#pragma once

#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

class Quad
{
protected:
	//�R���X�^���g�o�b�t�@
	struct CONSTANT_BUFFER
	{
		XMMATRIX matWVP;
		XMMATRIX matNormal;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;
	int index_;		//���_��
public:
	Quad();				//�R���X�g���N�^
	~Quad();			//�f�X�g���N�^
	virtual HRESULT Initialize();	//������
	HRESULT ConBuf();
	virtual HRESULT LoadTex();	//�e�N�X�`���̃��[�h
	void Draw(Transform& transform);	//�`��
	void Release();		//���
};