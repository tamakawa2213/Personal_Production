#include "Camera.h"
#include "CallDef.h"

//�ϐ�
namespace Camera {
	XMVECTOR position_;	//�J�����̈ʒu�i���_�j
	XMVECTOR target_;	//����ʒu�i�œ_�j
	XMMATRIX viewMatrix_;	//�r���[�s��
	XMMATRIX projMatrix_;	//�v���W�F�N�V�����s��


//������
	void Camera::Initialize(int winW, int winH)
	{
		position_ = XMVectorSet(NULL, 5, 1.4f, NULL);	//�J�����̈ʒu
		target_ = XMVectorSet(NULL, NULL, 1.5f, NULL);		//�J�����̏œ_
		projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH / 2.0f, 0.1f, 1000.0f);
	}

	//�X�V
	void Camera::Update()
	{
		//�r���[�s��̍쐬(�J�����Œ�̃Q�[���Ȃ�Initialize�ɏ���)
		viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	}

	//�ʒu��ݒ�
	void Camera::SetPosition(XMVECTOR position)
	{
		position_ = position;
	}

	void Camera::SetPosition(XMFLOAT3 position)
	{
		position_ = XMLoadFloat3(&position);
	}

	//�œ_��ݒ�
	void Camera::SetTarget(XMVECTOR target)
	{
		target_ = target;
	}

	//�r���[�s����擾
	XMMATRIX Camera::GetViewMatrix()
	{
		return viewMatrix_;
	}

	//�v���W�F�N�V�����s����擾
	XMMATRIX Camera::GetProjectionMatrix()
	{
		return projMatrix_;
	}
	XMFLOAT3 Camera::GetCameraPosition()
	{
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, position_);
		return pos;
	}
	XMFLOAT3 Camera::GetCameraTarget()
	{
		XMFLOAT3 tar;
		XMStoreFloat3(&tar, target_);
		return tar;
	}
	XMVECTOR GetCameraVecPosition()
	{
		return position_;
	}
	XMVECTOR GetCameraVecTarget()
	{
		return target_;
	}
}