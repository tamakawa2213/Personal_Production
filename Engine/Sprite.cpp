#include "Camera.h"
#include "Sprite.h"

Sprite::Sprite() :
	pVertexBuffer_(nullptr),	//頂点バッファ
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),	//コンスタントバッファ
	hr(S_OK),
	index_(nullptr),
	vertices_(nullptr),
	indexNum(0),
	vertexNum_(0),
	pTexture_(nullptr)
{
}

Sprite::~Sprite()
{
}


HRESULT Sprite::Initialize(LPCWSTR fileName)
{
	//頂点情報
	Vertex();
	hr = CreateVertexBuffer();

	//インデックス情報
	Index();
	hr = CreateIndexBuffer();

	//コンスタントバッファ作成
	hr = CreateConstantBuffer();

	//テクスチャのロード
	LoadTexture(fileName);

	return S_OK;
}

void Sprite::Draw(Transform& transform, XMFLOAT4 color)
{
	Direct3D::SetShader(SHADER_2D);
	Direct3D::SetDepthBafferWriteEnable(false);

	//コンスタントバッファに渡す情報
	transform.Calclation();
	PassDataToCB(transform, color);

	SetBufferToPipeline();
}

void Sprite::Release()
{
	SAFE_DELETE_ARRAY(vertices_);
	SAFE_DELETE_ARRAY(index_);
	SAFE_DELETE(pTexture_);
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}


///////////////ここからはprivate関数///////////////
void Sprite::Vertex()
{
	VERTEX vertices[] =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0, 0.0, 0.0f, 0.0f) },   // 四角形の頂点（左上）
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0, 0.0, 0.0f, 0.0f) },   // 四角形の頂点（右上）
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0, 1.0, 0.0f, 0.0f) },   // 四角形の頂点（右下）
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0, 1.0, 0.0f, 0.0f) },   // 四角形の頂点（左下）
	};
	vertexNum_ = sizeof(vertices) / sizeof(VERTEX);
	vertices_ = new VERTEX[vertexNum_];
	memcpy(vertices_, vertices, sizeof(vertices));
}

//頂点バッファを作成
HRESULT Sprite::CreateVertexBuffer()
{
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexNum_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices_;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

void Sprite::Index()
{
	int index[] = { 0,2,3, 0,1,2 };
	indexNum = sizeof(index) / sizeof(int);

	index_ = new int[indexNum];
	memcpy(index_, index, sizeof(index));
}

//インデックスバッファを作成
HRESULT Sprite::CreateIndexBuffer()
{
	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * indexNum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index_;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//コンスタントバッファ作成
HRESULT Sprite::CreateConstantBuffer()
{
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//テクスチャをロード
HRESULT Sprite::LoadTexture(LPCWSTR fileName)
{
	pTexture_ = new Texture;
	pTexture_->Load(fileName);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	return S_OK;
}

//コンスタントバッファに各種情報を渡す
void Sprite::PassDataToCB(Transform& transform, XMFLOAT4 color)
{
	CONSTANT_BUFFER cb;
	XMMATRIX mat = XMMatrixScaling(1.0f / (float)Direct3D::scrWidth, 1.0f / (float)Direct3D::scrHeight, 1.0f);	//Windows画面の調整
	cb.matW = XMMatrixTranspose(pTexture_->GetSize() * mat * transform.GetWorldMatrix());
	size_ = XMMatrixTranspose(pTexture_->GetSize() * mat);
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.color = color;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));					// データを値を送る

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(pConstantBuffer_, 0);										//再開
}

//各バッファをパイプラインにセット
void Sprite::SetBufferToPipeline()
{
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(indexNum, 0, 0);
	Direct3D::SetDepthBafferWriteEnable(true);
}

//レイキャスト
void Sprite::RayCast(RayCastData* data)
{
	data->hit = FALSE;
	for (int i = 0; i < 2; i++)
	{
		//3頂点
		XMVECTOR ver[3];

		ver[0] = vertices_[index_[i * 3 + 0]].position;
		ver[1] = vertices_[index_[i * 3 + 1]].position;
		ver[2] = vertices_[index_[i * 3 + 2]].position;

		//画像のサイズに合わせる
		ver[0] = XMVector3TransformCoord(ver[0], size_);
		ver[1] = XMVector3TransformCoord(ver[1], size_);
		ver[2] = XMVector3TransformCoord(ver[2], size_);

		XMFLOAT3 ver_[3];
		XMStoreFloat3(&ver_[0], ver[0]);
		XMStoreFloat3(&ver_[1], ver[1]);
		XMStoreFloat3(&ver_[2], ver[2]);

		BOOL  hit = FALSE;
		float dist = 0.0f;

		hit = Direct3D::Intersect(data->start, data->dir, ver_[0], ver_[1], ver_[2], &dist);

		if (hit && dist < data->dist)
		{
			data->hit = TRUE;
			data->dist = dist;
		}
	}
}