#include "Camera.h"
#include "Sprite.h"

Sprite::Sprite() :
	pVertexBuffer_(nullptr),	//���_�o�b�t�@
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),	//�R���X�^���g�o�b�t�@
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
	//���_���
	Vertex();
	hr = CreateVertexBuffer();

	//�C���f�b�N�X���
	Index();
	hr = CreateIndexBuffer();

	//�R���X�^���g�o�b�t�@�쐬
	hr = CreateConstantBuffer();

	//�e�N�X�`���̃��[�h
	LoadTexture(fileName);

	return S_OK;
}

void Sprite::Draw(Transform& transform, XMFLOAT4 color)
{
	Direct3D::SetShader(SHADER_2D);
	Direct3D::SetDepthBafferWriteEnable(false);

	//�R���X�^���g�o�b�t�@�ɓn�����
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


///////////////���������private�֐�///////////////
void Sprite::Vertex()
{
	VERTEX vertices[] =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0, 0.0, 0.0f, 0.0f) },   // �l�p�`�̒��_�i����j
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0, 0.0, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E��j
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0, 1.0, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�E���j
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0, 1.0, 0.0f, 0.0f) },   // �l�p�`�̒��_�i�����j
	};
	vertexNum_ = sizeof(vertices) / sizeof(VERTEX);
	vertices_ = new VERTEX[vertexNum_];
	memcpy(vertices_, vertices, sizeof(vertices));
}

//���_�o�b�t�@���쐬
HRESULT Sprite::CreateVertexBuffer()
{
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
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
		MessageBox(NULL, L"���_�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
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

//�C���f�b�N�X�o�b�t�@���쐬
HRESULT Sprite::CreateIndexBuffer()
{
	// �C���f�b�N�X�o�b�t�@�𐶐�����
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
		MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�R���X�^���g�o�b�t�@�쐬
HRESULT Sprite::CreateConstantBuffer()
{
	//�R���X�^���g�o�b�t�@�쐬
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// �R���X�^���g�o�b�t�@�̍쐬
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�e�N�X�`�������[�h
HRESULT Sprite::LoadTexture(LPCWSTR fileName)
{
	pTexture_ = new Texture;
	pTexture_->Load(fileName);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		return hr;
	}
	return S_OK;
}

//�R���X�^���g�o�b�t�@�Ɋe�����n��
void Sprite::PassDataToCB(Transform& transform, XMFLOAT4 color)
{
	CONSTANT_BUFFER cb;
	XMMATRIX mat = XMMatrixScaling(1.0f / (float)Direct3D::scrWidth, 1.0f / (float)Direct3D::scrHeight, 1.0f);	//Windows��ʂ̒���
	cb.matW = XMMatrixTranspose(pTexture_->GetSize() * mat * transform.GetWorldMatrix());
	size_ = XMMatrixTranspose(pTexture_->GetSize() * mat);
	D3D11_MAPPED_SUBRESOURCE pdata;
	cb.color = color;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));					// �f�[�^��l�𑗂�

	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->Unmap(pConstantBuffer_, 0);										//�ĊJ
}

//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
void Sprite::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p

	Direct3D::pContext->DrawIndexed(indexNum, 0, 0);
	Direct3D::SetDepthBafferWriteEnable(true);
}

//���C�L���X�g
void Sprite::RayCast(RayCastData* data)
{
	data->hit = FALSE;
	for (int i = 0; i < 2; i++)
	{
		//3���_
		XMVECTOR ver[3];

		ver[0] = vertices_[index_[i * 3 + 0]].position;
		ver[1] = vertices_[index_[i * 3 + 1]].position;
		ver[2] = vertices_[index_[i * 3 + 2]].position;

		//�摜�̃T�C�Y�ɍ��킹��
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