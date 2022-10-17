#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize(int WINDOW_WIDTH, int WINDOW_HEIGHT);

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target);

	//�r���[�s����擾
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix();
};