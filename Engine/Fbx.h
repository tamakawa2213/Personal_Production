#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

//�N���X�̑O���錾
class Texture;

struct RayCastData
{
	XMFLOAT3 start;
	XMFLOAT3 dir;
	float dist;
	bool hit;

	RayCastData() : start(), dir(), dist(9999.0f), hit(false) {}
};

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuseColor;
		XMFLOAT4	chroma;
		XMFLOAT4	light;
		int			isTexture;
		float		bright;
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer** pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	MATERIAL* pMaterialList_;
	int* indexCount_;
	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�
	VERTEX* pVertices_;	//���_�������\���̂̃|�C���^
	int** ppIndex_;
public:
	Fbx();
	~Fbx();
	HRESULT Load(std::string fileName);
	void InitVertex(fbxsdk::FbxMesh* pMesh);	//���_�o�b�t�@����
	void InitIndex(fbxsdk::FbxMesh* pMesh);	//�C���f�b�N�X�o�b�t�@����
	HRESULT IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	void RayCast(RayCastData& rayData);
	void Draw(Transform& transform);
	void Draw(Transform& transform, XMFLOAT3 Chroma, float Bright, float Alpha);	//transform, RGB�̒l, ���x(0 �`255)
	void Release();

	XMVECTOR NormalDotLight(Transform tr);
};