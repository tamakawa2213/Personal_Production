#include "Direct3D.h"
#include "Camera.h"
#include "CallDef.h"
#include <d3dcompiler.h>

//�ϐ�
namespace Direct3D
{
	//Direct3D�֘A
	ID3D11Device* pDevice = nullptr;						//�f�o�C�X
	ID3D11DeviceContext* pContext = nullptr;				//�f�o�C�X�R���e�L�X�g
	IDXGISwapChain* pSwapChain = nullptr;					//�X���b�v�`�F�C��
	ID3D11RenderTargetView* pRenderTargetView = nullptr;	//�����_�[�^�[�Q�b�g�r���[
	ID3D11Texture2D* pDepthStencil = nullptr;				//�[�x�X�e���V��
	ID3D11DepthStencilView* pDepthStencilView = nullptr;	//�[�x�X�e���V���r���[

	//�V�F�[�_�֘A
	struct SHADER {
		ID3D11VertexShader* pVertexShader = nullptr;		//���_�V�F�[�_�[
		ID3D11PixelShader* pPixelShader = nullptr;			//�s�N�Z���V�F�[�_�[
		ID3D11InputLayout* pVertexLayout = nullptr;			//���_�C���v�b�g���C�A�E�g
		ID3D11RasterizerState* pRasterizerState = nullptr;	//���X�^���C�U�[
	};
	SHADER shader[SHADER_MAX];

	int scrWidth, scrHeight;
}

//������
HRESULT Direct3D::Initialize(int winW, int winH, HWND hWnd)
{
	scrWidth = winW;
	scrHeight = winH;

	HRESULT hr;

	///////////////////////////���낢�돀�����邽�߂̐ݒ�///////////////////////////////
	//���낢��Ȑݒ荀�ڂ��܂Ƃ߂��\����
	DXGI_SWAP_CHAIN_DESC scDesc;

	//�Ƃ肠�����S��0
	ZeroMemory(&scDesc, sizeof(scDesc));

	//�`���̃t�H�[�}�b�g
	scDesc.BufferDesc.Width = winW;		//��ʕ�
	scDesc.BufferDesc.Height = winH;	//��ʍ���
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// ���F�g���邩

	//FPS�i1/60�b��1��j
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;

	//���̑�
	scDesc.Windowed = TRUE;			//�E�B���h�E���[�h���t���X�N���[����
	scDesc.OutputWindow = hWnd;		//�E�B���h�E�n���h��
	scDesc.BufferCount = 1;			//�o�b�N�o�b�t�@�̖���
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�o�b�N�o�b�t�@�̎g��������ʂɕ`�悷�邽�߂�
	scDesc.SampleDesc.Count = 1;		//MSAA�i�A���`�G�C���A�X�j�̐ݒ�
	scDesc.SampleDesc.Quality = 0;		//�@�V

	////////////////��L�ݒ�����ƂɃf�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C�����쐬////////////////////////
	D3D_FEATURE_LEVEL level;
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,						// �ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr��
		D3D_DRIVER_TYPE_HARDWARE,		// �h���C�o�̃^�C�v��n���B�ӂ���HARDWARE
		nullptr,						// ��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵�Ȃ�������nullptr
		0,								// ���炩�̃t���O���w�肷��B�i�f�o�b�O����D3D11_CREATE_DEVICE_DEBUG�H�j
		nullptr,						// �f�o�C�X�A�R���e�L�X�g�̃��x����ݒ�Bnullptr�ɂ��Ƃ���OK
		0,								// ��̈����Ń��x�������w�肵����
		D3D11_SDK_VERSION,				// SDK�̃o�[�W�����B�K�����̒l
		&scDesc,						// ��ł��낢��ݒ肵���\����
		&pSwapChain,					// ������������SwapChain�̃A�h���X���Ԃ��Ă���
		&pDevice,						// ������������Device�A�h���X���Ԃ��Ă���
		&level,							// ������������Device�AContext�̃��x�����Ԃ��Ă���
		&pContext);						// ������������Context�̃A�h���X���Ԃ��Ă���
	HR_FAILED(hr, L"�f�o�C�X�A�R���e�L�X�g�A�X���b�v�`�F�C���̍쐬�Ɏ��s���܂���");

	///////////////////////////�����_�[�^�[�Q�b�g�r���[�쐬///////////////////////////////
	//�X���b�v�`�F�[������o�b�N�o�b�t�@���擾�i�o�b�N�o�b�t�@ �� �����_�[�^�[�Q�b�g�j
	ID3D11Texture2D* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	assert(pBackBuffer != nullptr);

	//�����_�[�^�[�Q�b�g�r���[���쐬
	hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	HR_FAILED_RELEASE(hr, L"�����_�[�^�[�Q�b�g�r���[�̍쐬�Ɏ��s���܂���", pBackBuffer);
	
	//�����_�����O���ʂ�\������͈�
	D3D11_VIEWPORT vp[VpNum];
	vp[0].Width = (float)winW / 2;	//��
	vp[0].Height = (float)winH;//����
	vp[0].MinDepth = 0.0f;		//��O
	vp[0].MaxDepth = 1.0f;		//��
	vp[0].TopLeftX = 0;		//��
	vp[0].TopLeftY = 0;		//��

	vp[1].Width = (float)winW / 2;	//��
	vp[1].Height = (float)winH;//����
	vp[1].MinDepth = 0.0f;		//��O
	vp[1].MaxDepth = 1.0f;		//��
	vp[1].TopLeftX = (float)winW / 2;		//��
	vp[1].TopLeftY = 0;		//��

	//�[�x�X�e���V���r���[�̍쐬
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = winW;
	descDepth.Height = winH;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	pDevice->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
	assert(pDepthStencil != 0);
	pDevice->CreateDepthStencilView(pDepthStencil, NULL, &pDepthStencilView);

	//�f�[�^����ʂɕ`�悷�邽�߂̈�ʂ�̐ݒ�i�p�C�v���C���j
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	// �f�[�^�̓��͎�ނ��w��
	for (int i = NULL; i < VpNum; i++)
	{
		pContext->OMSetRenderTargets(i, &pRenderTargetView, pDepthStencilView);		// �`����ݒ�
		pContext->RSSetViewports(VpNum - i, &vp[i]);
	}
	

	//�V�F�[�_�[����(�����������Ȃ����̂ŕ���)
	hr = InitShader();
	if (FAILED(hr)) {//���s������Ahr(����)��return����
		return hr;
	}
	return S_OK;	//HRESULT�^�̖߂�l��Ԃ��K�v������
}

//�V�F�[�_�[����
HRESULT Direct3D::InitShader()
{
	HRESULT hr;

	hr = InitShader2D();
	assert(hr == S_OK);

	hr = InitShader3D();
	assert(hr == S_OK);

	return S_OK;
}

HRESULT Direct3D::InitShader2D()
{
	HRESULT hr;
	///////////////////////////////////////////////////// 2D�p /////////////////////////////////////////////////////////////////////

	// ���_�V�F�[�_(VertexShader)�̍쐬�i�R���p�C���j
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);	//�t�@�C�����J���Ȃ������ꍇ�A�������I������
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shader[SHADER_2D].pVertexShader);

	HR_FAILED_RELEASE(hr, L"���_�V�F�[�_�̍쐬�Ɏ��s���܂���",pCompileVS);

	//���_�C���v�b�g���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },					//�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(XMVECTOR), D3D11_INPUT_PER_VERTEX_DATA, 0 },	//UV���W
	};

	hr = pDevice->CreateInputLayout(layout, (UINT)std::size(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shader[SHADER_2D].pVertexLayout);
	HR_FAILED(hr, L"���_�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s���܂���");

	SAFE_RELEASE(pCompileVS);		//�R���p�C���������_�V�F�[�_�����

	// �s�N�Z���V�F�[�_(PixelShader)�̍쐬�i�R���p�C���j
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple2D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shader[SHADER_2D].pPixelShader);

	HR_FAILED_RELEASE(hr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s���܂���",pCompilePS);

	SAFE_RELEASE(pCompilePS);		//�R���p�C�������s�N�Z���V�F�[�_�����

	//���X�^���C�U�쐬
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shader[SHADER_2D].pRasterizerState);

	HR_FAILED(hr, L"���X�^���C�U�̍쐬�Ɏ��s���܂���");

	return S_OK;
}

HRESULT Direct3D::InitShader3D()
{
	HRESULT hr;
	///////////////////////////////////////////////// 3D�p /////////////////////////////////////////////////////////////////

	// ���_�V�F�[�_(VertexShader)�̍쐬�i�R���p�C���j
	ID3DBlob* pCompileVS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "VS", "vs_5_0", NULL, 0, &pCompileVS, NULL);
	assert(pCompileVS != nullptr);	//�t�@�C�����J���Ȃ������ꍇ�A�������I������
	hr = pDevice->CreateVertexShader(pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), NULL, &shader[SHADER_3D].pVertexShader);
	HR_FAILED_RELEASE(hr, L"���_�V�F�[�_�̍쐬�Ɏ��s���܂���", pCompileVS);

	//���_�C���v�b�g���C�A�E�g
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },						//�ʒu
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT	, 0, sizeof(XMVECTOR), D3D11_INPUT_PER_VERTEX_DATA, 0 },		//UV���W
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(XMVECTOR) * 2 ,	D3D11_INPUT_PER_VERTEX_DATA, 0 },	//�@��
	};
	hr = pDevice->CreateInputLayout(layout, (UINT)std::size(layout), pCompileVS->GetBufferPointer(), pCompileVS->GetBufferSize(), &shader[SHADER_3D].pVertexLayout);

	HR_FAILED(hr, L"���_�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s���܂���");

	SAFE_RELEASE(pCompileVS);		//�R���p�C���������_�V�F�[�_�����

	// �s�N�Z���V�F�[�_(PixelShader)�̍쐬�i�R���p�C���j
	ID3DBlob* pCompilePS = nullptr;
	D3DCompileFromFile(L"Simple3D.hlsl", nullptr, nullptr, "PS", "ps_5_0", NULL, 0, &pCompilePS, NULL);
	assert(pCompilePS != nullptr);
	hr = pDevice->CreatePixelShader(pCompilePS->GetBufferPointer(), pCompilePS->GetBufferSize(), NULL, &shader[SHADER_3D].pPixelShader);

	HR_FAILED_RELEASE(hr, L"�s�N�Z���V�F�[�_�̍쐬�Ɏ��s���܂���", pCompilePS);

	SAFE_RELEASE(pCompilePS);		//�R���p�C�������s�N�Z���V�F�[�_�����

	//���X�^���C�U�쐬
	D3D11_RASTERIZER_DESC rdc = {};
	rdc.CullMode = D3D11_CULL_BACK;
	rdc.FillMode = D3D11_FILL_SOLID;
	rdc.FrontCounterClockwise = FALSE;
	hr = pDevice->CreateRasterizerState(&rdc, &shader[SHADER_3D].pRasterizerState);

	HR_FAILED(hr, L"���X�^���C�U�̍쐬�Ɏ��s���܂���");
	return S_OK;
}

void Direct3D::SetShader(int type)
{
	//���ꂼ����f�o�C�X�R���e�L�X�g�ɃZ�b�g
	pContext->VSSetShader(shader[type].pVertexShader, NULL, 0);	//���_�V�F�[�_�[
	pContext->PSSetShader(shader[type].pPixelShader, NULL, 0);	//�s�N�Z���V�F�[�_�[
	pContext->IASetInputLayout(shader[type].pVertexLayout);		//���_�C���v�b�g���C�A�E�g
	pContext->RSSetState(shader[type].pRasterizerState);		//���X�^���C�U
}

//�`��J�n
void Direct3D::BeginDraw()
{
	//�w�i�̐F
	float clearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };//R,G,B,A

	//��ʂ��N���A
	pContext->ClearRenderTargetView(pRenderTargetView, clearColor);
	
	Camera::Update();

	//�[�x�o�b�t�@�N���A
	pContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

//�`��I��
void Direct3D::EndDraw()
{
	//�X���b�v�i�o�b�N�o�b�t�@��\�ɕ\������j
	pSwapChain->Present(0, 0);
}

//�������
void Direct3D::Release()
{
	for (int i = 0; i < SHADER_MAX; i++) {
		SAFE_RELEASE(shader[i].pRasterizerState);
		SAFE_RELEASE(shader[i].pVertexLayout);
		SAFE_RELEASE(shader[i].pPixelShader);
		SAFE_RELEASE(shader[i].pVertexShader);
	}
	SAFE_RELEASE(pRenderTargetView);
	SAFE_RELEASE(pSwapChain);
	SAFE_RELEASE(pContext);
	SAFE_RELEASE(pDevice);
}