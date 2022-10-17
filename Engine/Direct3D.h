#pragma once
#include <assert.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include "CallDef.h"

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

namespace Direct3D
{
	extern ID3D11Device* pDevice;				//デバイス
	extern ID3D11DeviceContext* pContext;		//デバイスコンテキスト
	extern int scrWidth, scrHeight;			//スクリーンの幅と高さ

	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();

	//スクリーンの色の取得
	void SetColor(float red, float blue, float green);

	//ZバッファのON,OFF
	void SetDepthBafferWriteEnable(bool isWrite);

	//三角形と線分の衝突判定
	bool Intersect(XMFLOAT3& start, XMFLOAT3& direction, XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2, float* distance);
};