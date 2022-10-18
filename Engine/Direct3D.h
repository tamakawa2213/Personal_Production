#pragma once
//#ifndef _DIRECT3D_H_
//#define _DIRECT3D_H_

#include <assert.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <iterator>

using namespace DirectX;

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

enum SHADER_TYPE {
	SHADER_2D,	//2D�p�V�F�[�_�[
	SHADER_3D,	//3D�p�V�F�[�_�[
	SHADER_MAX	//����͎g��Ȃ�
};

namespace Direct3D
{
//extern = �ǂ����Ő�������Ă��āA�����񐶐�����Ȃ��悤�ɂ��邽�߂̂���
	extern ID3D11Device* pDevice;			//�f�o�C�X
	extern ID3D11DeviceContext* pContext;	//�f�o�C�X�R���e�L�X�g
	extern int scrWidth, scrHeight;			//�X�N���[���̕��ƍ���

	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();

	void SetShader(int type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();
};

//#endif