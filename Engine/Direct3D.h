#pragma once
//#ifndef _DIRECT3D_H_
//#define _DIRECT3D_H_

#include <assert.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <iterator>

using namespace DirectX;

//リンカ
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE {
	SHADER_2D,	//2D用シェーダー
	SHADER_3D,	//3D用シェーダー
	SHADER_MAX	//これは使わない
};

namespace Direct3D
{
//extern = どこかで生成されていて、複数回生成されないようにするためのもの
	extern ID3D11Device* pDevice;			//デバイス
	extern ID3D11DeviceContext* pContext;	//デバイスコンテキスト
	extern int scrWidth, scrHeight;			//スクリーンの幅と高さ

	//初期化
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備
	HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();

	void SetShader(int type);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();
};

//#endif