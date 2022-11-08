#include "Camera.h"
#include "CallDef.h"

//�ϐ�
namespace Camera {
	XMVECTOR position_[VpNum];	//�J�����̈ʒu�i���_�j
	XMVECTOR target_[VpNum];	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_[VpNum];	//�r���[�s��
	XMMATRIX projMatrix_[VpNum];	//�v���W�F�N�V�����s��


//������
	void Camera::Initialize(int winW, int winH)
	{
		for (int i = NULL; i < VpNum; i++)
		{
			position_[i] = XMVectorSet(NULL, 5, 1.4f + i, NULL);	//�J�����̈ʒu
			target_[i] = XMVectorSet(NULL, NULL, 1.5f, NULL);		//�J�����̏œ_
			projMatrix_[i] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH, 0.1f, 100.0f);	//�v���W�F�N�V�����s��
		}
	}

	//�X�V
	void Camera::Update()
	{
		for (int i = NULL; i < VpNum; i++)
		{
			//�r���[�s��̍쐬(�J�����Œ�̃Q�[���Ȃ�Initialize�ɏ���)
			viewMatrix_[i] = XMMatrixLookAtLH(position_[i], target_[i], XMVectorSet(0, 1, 0, 0));
		}
	}

	//�ʒu��ݒ�
	void Camera::SetPosition(XMVECTOR position, int CameraNum)
	{
		position_[CameraNum] = position;
	}

	//�œ_��ݒ�
	void Camera::SetTarget(XMVECTOR target, int CameraNum)
	{
		target_[CameraNum] = target;
	}

	//�r���[�s����擾
	XMMATRIX Camera::GetViewMatrix(int CameraNum)
	{
		return viewMatrix_[CameraNum];
	}
	XMMATRIX Camera::GetViewMatrix()
	{
		return viewMatrix_[NULL];
	}

	//�v���W�F�N�V�����s����擾
	XMMATRIX Camera::GetProjectionMatrix(int CameraNum)
	{
		return projMatrix_[CameraNum];
	}
	XMMATRIX Camera::GetProjectionMatrix()
	{
		return projMatrix_[NULL];
	}
}