#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>

using namespace DirectX;

//-----------------------------------------------------------
//�J����
//-----------------------------------------------------------
namespace Camera
{
	//�������i�v���W�F�N�V�����s��쐬�j
	void Initialize(int winW, int winH);

	//�X�V�i�r���[�s��쐬�j
	void Update();

	//���_�i�J�����̈ʒu�j��ݒ�
	void SetPosition(XMVECTOR position, int CameraNum);

	//�œ_�i����ʒu�j��ݒ�
	void SetTarget(XMVECTOR target, int CameraNum);

	//�r���[�s����擾
	XMMATRIX GetViewMatrix(int CameraNum);
	XMMATRIX GetViewMatrix();

	//�v���W�F�N�V�����s����擾
	XMMATRIX GetProjectionMatrix(int CameraNum);
	XMMATRIX GetProjectionMatrix();
};