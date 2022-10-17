#pragma once
#include <d3d11.h>
#include "string"

//レイキャスト用構造体
struct RayCastData
{
	XMFLOAT3	start;	//レイ発射位置
	XMFLOAT3	dir;	//レイの向きベクトル
	float       dist;	//衝突点までの距離
	BOOL        hit;	//レイが当たったか
	XMFLOAT3 normal;	//法線

	RayCastData() : start(), dir(), dist(), hit(), normal() { dist = 99999.0f; }
};

class Texture
{
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
	XMMATRIX size_;
public:
	Texture();
	~Texture();
	HRESULT Load(LPCWSTR fileName);
	void Release();

	ID3D11SamplerState* GetSampler() { return pSampler_; }
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; }
	XMMATRIX GetSize() { return size_; }
};