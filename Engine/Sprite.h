#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

class Sprite
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
		XMFLOAT4	color;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	DWORD	vertexNum_;		//���_��
	VERTEX* vertices_;		//���_���
	ID3D11Buffer* pVertexBuffer_;		//���_�o�b�t�@
	HRESULT hr;

	DWORD indexNum;			//�C���f�b�N�X��
	int* index_;			//�C���f�b�N�X���
	ID3D11Buffer* pIndexBuffer_;		//�C���f�b�N�X�o�b�t�@

	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	Texture* pTexture_;		//�e�N�X�`��

public:
	Sprite();
	~Sprite();
	HRESULT Initialize(LPCWSTR fileName);
	void Draw(Transform& transform, XMFLOAT4 color);
	void Release();
	void RayCast(RayCastData* data);
private:
	XMMATRIX size_;	//�摜�̃T�C�Y
	virtual void Index();
	HRESULT CreateVertexBuffer();		//���_�o�b�t�@���쐬

	virtual void Vertex();
	HRESULT CreateIndexBuffer();		//�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer();		//�R���X�^���g�o�b�t�@�쐬

	HRESULT LoadTexture(LPCWSTR fileName);				//�e�N�X�`�������[�h


	//---------Draw�֐�����Ă΂��֐�---------
	void PassDataToCB(Transform& transform, XMFLOAT4 color);	//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();							//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
};