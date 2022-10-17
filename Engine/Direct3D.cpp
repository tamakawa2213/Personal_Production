#include <d3dcompiler.h>
#include "Direct3D.h"


//変数
namespace Direct3D
{
	ID3D11Device* pDevice;						//デバイス
	ID3D11DeviceContext* pContext;				//デバイスコンテキスト
	IDXGISwapChain* pSwapChain;					//スワップチェイン
	ID3D11RenderTargetView* pRenderTargetView;	//レンダーターゲットビュー
	ID3D11Texture2D* pDepthStencil;			//深度ステンシル
	ID3D11BlendState* pBlendState;				//ブレンドステート(透明の表現方法のこと	)
	ID3D11DepthStencilView* pDepthStencilView;		//深度ステンシルビュー

	//スクリーンの色
	float red_;
	float blue_;
	float green_;

	struct SHADER_BUNDLE
	{
		ID3D11VertexShader* pVertexShader = nullptr;	//頂点シェーダー
		ID3D11PixelShader* pPixelShader = nullptr;		//ピクセルシェーダー
		ID3D11InputLayout* pVertexLayout = nullptr;		//頂点インプットレイアウト
		ID3D11RasterizerState* pRasterizerState = nullptr;	//ラスタライザー
	};
	SHADER_BUNDLE shaderBundle[SHADER_MAX];

	int scrWidth, scrHeight;
}

//初期化
HRESULT Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
	scrWidth = winW;
	scrHeight = winH;
	HRESULT hr;

	///////////////////////////いろいろ準備するための設定///////////////////////////////
	//いろいろな設定項目をまとめた構造体
	DXGI_SWAP_CHAIN_DESC scDesc;

	//とりあえず全部0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//描画先のフォーマット
	scDesc.BufferDesc.Width = winW;//画面幅
	scDesc.BufferDesc.Height = winH;	//画面高さ
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 何色使えるか

	//FPS（1/60秒に1回）
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//その他
	scDesc.Windowed = TRUE;			//ウィンドウモードかフルスクリーンか
	scDesc.OutputWindow = hWnd;		//ウィンドウハンドル
	scDesc.BufferCount = 1;			//バックバッファの枚数
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//バックバッファの使い道＝画面に描画するために
	scDesc.SampleDesc.Count = 1;		//MSAA（アンチエイリアス）の設定
	scDesc.SampleDesc.Quality = 0;		//　〃

	////////////////上記設定をもとにデバイス、コンテキスト、スワップチェインを作成////////////////////////
	D3D_FEATURE_LEVEL level;
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,						// どのビデオアダプタを使用するか？既定ならばnullptrで
		D3D_DRIVER_TYPE_HARDWARE,		// ドライバのタイプを渡す。ふつうはHARDWARE
		nullptr,						// 上記をD3D_DRIVER_TYPE_SOFTWAREに設定しないかぎりnullptr
		0,								// 何らかのフラグを指定する。（デバッグ時はD3D11_CREATE_DEVICE_DEBUG？）
		nullptr,						// デバイス、コンテキストのレベルを設定。nullptrにしとけばOK
		0,								// 上の引数でレベルを何個指定したか
		D3D11_SDK_VERSION,				// SDKのバージョン。必ずこの値
		&scDesc,						// 上でいろいろ設定した構造体
		&pSwapChain,					// 無事完成したSwapChainのアドレスが返ってくる
		&pDevice,						// 無事完成したDeviceアドレスが返ってくる
		&level,							// 無事完成したDevice、Contextのレベルが返ってくる
		&pContext);						// 無事完成したContextのアドレスが返ってくる

	if (FAILED(hr))
	{
		MessageBox(NULL, L"デバイス、コンテキスト、スワップチェインの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	///////////////////////////レンダーターゲットビュー作成///////////////////////////////
	//スワップチェーンからバックバッファを取得（バックバッファ ＝ レンダーターゲット）
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//レンダーターゲットビューを作成
	assert(pBackBuffer != nullptr);
	hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"レンダーターゲットビューの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	//一時的にバックバッファを取得しただけなので解放
	pBackBuffer->Release();


	///////////////////////////ビューポート（描画範囲）設定///////////////////////////////
	//レンダリング結果を表示する範囲
	D3D11_VIEWPORT vp;
	vp.Width = (float)winW;	//幅
	vp.Height = (float)winH;//高さ
	vp.MinDepth = 0.0f;	//手前
	vp.MaxDepth = 1.0f;	//奥
	vp.TopLeftX = 0;	//左
	vp.TopLeftY = 0;	//上


	//深度ステンシルビューの作成
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = winW;
	descDepth.Height = winH;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(pDepthStencil != nullptr);
	pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);

	//ブレンドステートの作成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	pDevice->CreateBlendState(&BlendDesc, &pBlendState);
	float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	pContext->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);

	//データを画面に描画するための一通りの設定（パイプライン）
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);  // データの入力種類を指定
	pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);            // 描画先を設定
	pContext->RSSetViewports(1, &vp);

	//スクリーンの色
	red_ = 0;
	blue_ = 0.5;
	green_ = 0.5;

	//シェーダー準備
	hr = InitShader();
	if (FAILED(hr))
	{
		return hr;
	}

	return S_OK;
}

//シェーダー準備
HRESULT Direct3D::InitShader()
{
	if (FAILED(InitShader3D()))
	{
		return E_FAIL;
	}

	if (FAILED(InitShader2D()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Direct3D::InitShader3D()
{
	HRESULT hr;

	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);

	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点シェーダーの作成に失敗しました", L"エラー", MB_OK);
		SAFE_RELEASE(pCompileVS);
		return hr;
	}



	//頂点インプットレイアウト
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//UV
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//法線
	};
	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_3D].pVertexLayout);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点インプットレイアウトの作成に失敗しました", L"エラー", MB_OK);
		SAFE_RELEASE(pCompileVS);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_3D].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ピクセルシェーダの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}



	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[SHADER_3D].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ラスタライザの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

HRESULT Direct3D::InitShader2D()
{
	HRESULT hr;

	// 頂点シェーダの作成（コンパイル）
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);

	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点シェーダーの作成に失敗しました", L"エラー", MB_OK);
		SAFE_RELEASE(pCompileVS);
		return hr;
	}



	//頂点インプットレイアウト
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//位置
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(XMVECTOR),  D3D11_INPUT_PER_VERTEX_DATA, 0 },	//UV
	};
	hr = pDevice->CreateInputLayout(layout, sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shaderBundle[SHADER_2D].pVertexLayout);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点インプットレイアウトの作成に失敗しました", L"エラー", MB_OK);
		SAFE_RELEASE(pCompileVS);
		return hr;
	}
	SAFE_RELEASE(pCompileVS);

	// ピクセルシェーダの作成（コンパイル）
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shaderBundle[SHADER_2D].pPixelShader);
	SAFE_RELEASE(pCompilePS);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ピクセルシェーダの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	//ラスタライザ作成
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shaderBundle[SHADER_2D].pRasterizerState);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ラスタライザの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

void Direct3D::SetShader(SHADER_TYPE type)
{
	//それぞれをデバイスコンテキストにセット
	pContext->VSSetShader(shaderBundle[type].pVertexShader, NULL, 0);	//頂点シェーダー
	pContext->PSSetShader(shaderBundle[type].pPixelShader, NULL, 0);	//ピクセルシェーダー
	pContext->IASetInputLayout(shaderBundle[type].pVertexLayout);		//頂点インプットレイアウト
	pContext->RSSetState(shaderBundle[type].pRasterizerState);			//ラスタライザー


}


//描画開始
void Direct3D::BeginDraw()
{
	//背景の色
	float clearColor[4] = { red_, green_, blue_, 1.0f };//R,G,B,A

	//画面をクリア
	pContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	//深度バッファクリア
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//描画終了
void Direct3D::EndDraw()
{

	//スワップ（バックバッファを表に表示する）
	pSwapChain->Present(0, 0);
}

//解放処理
void Direct3D::Release()
{
	//解放処理
	for (int i = 0; i < SHADER_MAX; i++)
	{
		SAFE_RELEASE(shaderBundle[i].pRasterizerState);
		SAFE_RELEASE(shaderBundle[i].pVertexLayout);
		SAFE_RELEASE(shaderBundle[i].pPixelShader);
		SAFE_RELEASE(shaderBundle[i].pVertexShader);
	}

	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);
	SAFE_RELEASE(pContext);
	SAFE_RELEASE(pDevice);
}

//スクリーンの色の取得
void Direct3D::SetColor(float red, float blue, float green)
{
	red_ = red;
	blue_ = blue;
	green_ = green;
}

void Direct3D::SetDepthBafferWriteEnable(bool isWrite)
{
	//ON
	if (isWrite)
	{
		//Zバッファ（デプスステンシルを指定する）
		pContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
	}

	//OFF
	else
	{
		pContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
	}
}

//三角形と線分の衝突判定
bool  Direct3D::Intersect(XMFLOAT3& start, XMFLOAT3& direction, XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2, float* distance)
{
	// 微小な定数での値
	constexpr float kEpsilon = 1e-6f;

	//三角形の２辺
	XMVECTOR edge1 = XMVectorSet(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z, 0.0f);
	XMVECTOR edge2 = XMVectorSet(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z, 0.0f);

	XMVECTOR alpha = XMVector3Cross(XMLoadFloat3(&direction), edge2);
	float det = XMVector3Dot(edge1, alpha).m128_f32[0];

	if (-kEpsilon < det && det < kEpsilon)
	{
		return false;
	}

	float invDet = 1.0f / det;
	XMFLOAT3 r = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);

	// uが0 <= u<=1 を満たしているかを調べる。
	float u = XMVector3Dot(alpha, XMLoadFloat3(&r)).m128_f32[0] * invDet;
	if (u < 0.0f || u > 1.0f)
	{
		return false;
	}

	XMVECTOR beta = XMVector3Cross(XMLoadFloat3(&r), edge1);

	// vが0 <= v<=1 - u をみたしているかを調べる
	float v = XMVector3Dot(XMLoadFloat3(&direction), beta).m128_f32[0] * invDet;
	if (v < 0.0f || u + v > 1.0f)
	{
		return false;
	}

	// tが0 <= t を満たすことを調べる。
	float t = XMVector3Dot(edge2, beta).m128_f32[0] * invDet;
	if (t < 0.0f)
	{
		return false;
	}

	*distance = t;
	return true;
}