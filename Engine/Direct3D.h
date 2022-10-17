#pragma once
#include <assert.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include "CallDef.h"

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

namespace Direct3D
{
	extern ID3D11Device* pDevice;				//�f�o�C�X
	extern ID3D11DeviceContext* pContext;		//�f�o�C�X�R���e�L�X�g
	extern int scrWidth, scrHeight;			//�X�N���[���̕��ƍ���

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader3D();
	HRESULT InitShader2D();

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

	//�X�N���[���̐F�̎擾
	void SetColor(float red, float blue, float green);

	//Z�o�b�t�@��ON,OFF
	void SetDepthBafferWriteEnable(bool isWrite);

	//�O�p�`�Ɛ����̏Փ˔���
	bool Intersect(XMFLOAT3& start, XMFLOAT3& direction, XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2, float* distance);
};