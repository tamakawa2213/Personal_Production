#pragma once
#include <d3d11.h>
#include "string"

////���C�L���X�g�p�\����
//struct RayCastData
//{
//	XMFLOAT3	start;	//���C���ˈʒu
//	XMFLOAT3	dir;	//���C�̌����x�N�g��
//	float       dist;	//�Փ˓_�܂ł̋���
//	BOOL        hit;	//���C������������
//	XMFLOAT3 normal;	//�@��
//
//	RayCastData() : start(), dir(), dist(), hit(), normal() { dist = 99999.0f; }
//};

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