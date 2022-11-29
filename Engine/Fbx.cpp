#include "Fbx.h"
#include "Camera.h"
#include "CallDef.h"
#include "Direct3D.h"
#include "Texture.h"
#include "Math.h"

Fbx::Fbx() :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr), pMaterialList_(nullptr), indexCount_(nullptr),
vertexCount_(0), polygonCount_(0), materialCount_(0), pVertices_(nullptr), ppIndex_(nullptr)
{
}

Fbx::~Fbx()
{
	Release();
}

HRESULT Fbx::Load(std::string fileName)
{
	HRESULT hr;
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//���b�V�������擾
	FbxNode* pRootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = pRootNode->GetChild(0);
	FbxMesh* pMesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = pMesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = pMesh->GetPolygonCount();		//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();		//�}�e���A���̐�
	//���݂̃J�����g�f�B���N�g�����o���Ă���
	WCHAR defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//������fileName����f�B���N�g���������擾
	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());
	WCHAR dir[MAX_PATH];
	_wsplitpath_s(wtext, nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
	//�J�����g�f�B���N�g���ύX
	SetCurrentDirectory(dir);

	InitVertex(pMesh);			//���_�o�b�t�@����
	InitIndex(pMesh);			//�C���f�b�N�X�o�b�t�@����
	hr = IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	assert(hr == S_OK);
	InitMaterial(pNode);		//�}�e���A������

	//�J�����g�f�B���N�g�������ɖ߂�
	SetCurrentDirectory(defaultCurrentDir);

	//�}�l�[�W�����
	pFbxManager->Destroy();

	return S_OK;
}

void Fbx::InitVertex(fbxsdk::FbxMesh* pMesh)
{
	//���_��������z��
	pVertices_ = new VERTEX[vertexCount_];

	//�S�|���S��
	for (DWORD poly = 0; poly < (unsigned)polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < (unsigned)3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = pMesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = pMesh->GetControlPointAt(index);
			pVertices_[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//���_��UV
			FbxLayerElementUV* pUV = pMesh->GetLayer(0)->GetUVs();
			int uvIndex = pMesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			pVertices_[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//���_�̖@��
			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(poly, vertex, Normal);	//���Ԗڂ̃|���S���́A���Ԗڂ̒��_�̖@�����Q�b�g
			pVertices_[index].normal = XMVectorSet((float)Normal[0], (float)Normal[1], (float)Normal[2], 0.0f);
		}
	}
	// ���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = pVertices_;
	Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

void Fbx::InitIndex(fbxsdk::FbxMesh* pMesh)
{
	int VertexCount = polygonCount_ * 3;
	pIndexBuffer_ = new ID3D11Buffer * [materialCount_];
	indexCount_ = new int[materialCount_];

	ppIndex_ = new int* [materialCount_];
	for (int i = 0; i < materialCount_; i++)
	{
		ppIndex_[i] = new int[VertexCount];
	}

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;

		//�S�|���S��
		for (DWORD poly = 0; poly < (unsigned)polygonCount_; poly++)
		{
			FbxLayerElementMaterial* mtl = pMesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			if (mtlId == i)
			{
				//3���_��
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					ppIndex_[i][count] = pMesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;
		D3D11_BUFFER_DESC   bd;
		bd.ByteWidth = sizeof(int) * VertexCount;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = ppIndex_[i];
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		HRESULT hr;
		hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
		assert(hr == S_OK);
	}
}

HRESULT Fbx::IntConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	HR_FAILED(hr, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���");

	return hr;
}

void Fbx::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = new MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�e�N�X�`���̐���
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//�e�N�X�`������
		if (fileTextureCount != 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//�t�@�C����+�g�������ɂ���
			char name[_MAX_FNAME];	//�t�@�C����
			char ext[_MAX_EXT];	//�g���q
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			sprintf_s(name, "%s%s", name, ext);

			//�t�@�C������e�N�X�`���쐬
			pMaterialList_[i].pTexture = new Texture;
			wchar_t wtext[FILENAME_MAX];
			size_t ret;
			mbstowcs_s(&ret, wtext, name, strlen(textureFilePath));
			HRESULT hr;
			hr = pMaterialList_[i].pTexture->Load(wtext);
			assert(hr == S_OK);
		}

		//�e�N�X�`������
		else
		{
			pMaterialList_[i].pTexture = nullptr;

			//�}�e���A���̐F
			FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			FbxDouble3  diffuse = pMaterial->Diffuse;
			pMaterialList_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);
		}

	}

}

void Fbx::RayCast(RayCastData& rayData)
{
	rayData.hit = false;
	XMVECTOR normal = XMLoadFloat3(&rayData.dir);
	normal = XMVector4Normalize(normal);
	XMStoreFloat3(&rayData.dir, normal);

	for (int material = 0; material < materialCount_; material++)
	{
		for (int poly = 0; poly < indexCount_[material] / 3; poly++)
		{
			XMFLOAT3 v0; XMStoreFloat3(&v0, pVertices_[ppIndex_[material][poly * 3]].position);
			XMFLOAT3 v1; XMStoreFloat3(&v1, pVertices_[ppIndex_[material][poly * 3 + 1]].position);
			XMFLOAT3 v2; XMStoreFloat3(&v2, pVertices_[ppIndex_[material][poly * 3 + 2]].position);
			rayData.hit = Math::Intersect(rayData.start, rayData.dir, v0, v1, v2, &rayData.dist);

			if (rayData.hit)
			{
				return;
			}
		}

	}
}


void Fbx::Draw(Transform& transform)
{
	Draw(transform, XMFLOAT3(0.3f, 0.3f, 0.3f), UCHAR_MAX, UCHAR_MAX);
}

void Fbx::Draw(Transform& transform, XMFLOAT3 Chroma, float Bright, float Alpha)
{
	Direct3D::SetShader(SHADER_3D);


	for (int i = 0; i < materialCount_; i++)
	{
		CLAMP(Chroma.x, 0, 1);
		CLAMP(Chroma.y, 0, 1);
		CLAMP(Chroma.z, 0, 1);
		CLAMP(Alpha, 0, 1);

		CONSTANT_BUFFER cb;
		transform.Calclation();
		cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());	//�s��Ȃ̂ŏ��Ԃ͌Œ�
		cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix());
		cb.chroma = XMFLOAT4(Chroma.x, Chroma.y, Chroma.z, Alpha);
		cb.bright = Bright;

		cb.light = XMFLOAT4(-0.5f, 0.7f, 1.0f, 0.0f);
		/*XMFLOAT3 lgt;
		XMStoreFloat3(&lgt, NormalDotLight(transform));
		cb.light = XMFLOAT4(lgt.x, lgt.y, lgt.z, 0);*/

		if (pMaterialList_[i].pTexture == nullptr) {
			cb.isTexture = FALSE;
			cb.diffuseColor = pMaterialList_[i].diffuse;
		}
		else {
			cb.isTexture = TRUE;
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
		}

		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�

		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		// �f�[�^��l�𑗂�

		Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ

		//���_�o�b�t�@
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

		//�C���f�b�N�X�o�b�t�@���Z�b�g
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//�R���X�^���g�o�b�t�@
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
		Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
	}

}

void Fbx::Release()
{
	for (int i = 0; i < materialCount_; i++)
	{
		SAFE_DELETE_ARRAY(ppIndex_);
	}
	SAFE_DELETE_ARRAY(ppIndex_);
	SAFE_DELETE_ARRAY(pVertices_);
	SAFE_RELEASE(pConstantBuffer_);
	for (int i = 0; i < materialCount_; i++) {
		SAFE_DELETE_ARRAY(pIndexBuffer_);
	}
	SAFE_DELETE_ARRAY(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}

XMVECTOR Fbx::NormalDotLight(Transform tr)
{
	XMMATRIX matInv = XMMatrixInverse(nullptr, tr.GetWorldMatrix());
	float dot = 0.0f;
	XMVECTOR sight = XMVector3TransformCoord(Camera::GetCameraVecTarget(), matInv) - XMVector3TransformCoord(Camera::GetCameraVecPosition(), matInv);
	sight = XMVector3Normalize(sight);
	XMVECTOR ans = sight;
	for (int material = 0; material < materialCount_; material++)
	{
		for (int poly = 0; poly < indexCount_[material] / 3; poly++)
		{
			XMVECTOR v[3], cross;
			v[0] = pVertices_[ppIndex_[material][poly * 3]].position;
			v[1] = pVertices_[ppIndex_[material][poly * 3 + 1]].position;
			v[2] = pVertices_[ppIndex_[material][poly * 3 + 2]].position;
			
			cross = XMVector3Cross(v[2] - v[0], v[1] - v[0]);
			cross = XMVector3Normalize(cross);
			float sto = XMVectorGetX(XMVector3Dot(sight, cross));

			if (sto < 0)
			{
				sto = -sto;
			}

			if (dot < sto)
			{
				dot = sto;
				ans = -cross;
			}
		}

	}
	return ans;
}
