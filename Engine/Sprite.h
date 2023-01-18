#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

class Sprite
{
protected:
	//�R���X�^���g�o�b�t�@
	struct CONSTANT_BUFFER
	{
		XMMATRIX matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;
	int index_;		//���_��

public:
	Sprite();				//�R���X�g���N�^
	~Sprite();				//�f�X�g���N�^
	virtual HRESULT Initialize(LPCWSTR filename);	//������
	HRESULT ConBuf(LPCWSTR filename);
	virtual HRESULT Load(LPCWSTR filename);
	//Transform�������ɂƂ�
	void Draw(Transform& transform);	//�`��
	void Release();						//���
	UINT GetImgWidth();
	UINT GetImgHeight();
};