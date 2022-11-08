#include "Camera.h"
#include "CallDef.h"

//変数
namespace Camera {
	XMVECTOR position_[VpNum];	//カメラの位置（視点）
	XMVECTOR target_[VpNum];	//見る位置（焦点）
	XMMATRIX viewMatrix_[VpNum];	//ビュー行列
	XMMATRIX projMatrix_[VpNum];	//プロジェクション行列


//初期化
	void Camera::Initialize(int winW, int winH)
	{
		for (int i = NULL; i < VpNum; i++)
		{
			position_[i] = XMVectorSet(NULL, 5, 1.4f + i, NULL);	//カメラの位置
			target_[i] = XMVectorSet(NULL, NULL, 1.5f, NULL);		//カメラの焦点
			projMatrix_[i] = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)winW / (FLOAT)winH, 0.1f, 100.0f);	//プロジェクション行列
		}
	}

	//更新
	void Camera::Update()
	{
		for (int i = NULL; i < VpNum; i++)
		{
			//ビュー行列の作成(カメラ固定のゲームならInitializeに書く)
			viewMatrix_[i] = XMMatrixLookAtLH(position_[i], target_[i], XMVectorSet(0, 1, 0, 0));
		}
	}

	//位置を設定
	void Camera::SetPosition(XMVECTOR position, int CameraNum)
	{
		position_[CameraNum] = position;
	}

	//焦点を設定
	void Camera::SetTarget(XMVECTOR target, int CameraNum)
	{
		target_[CameraNum] = target;
	}

	//ビュー行列を取得
	XMMATRIX Camera::GetViewMatrix(int CameraNum)
	{
		return viewMatrix_[CameraNum];
	}
	XMMATRIX Camera::GetViewMatrix()
	{
		return viewMatrix_[NULL];
	}

	//プロジェクション行列を取得
	XMMATRIX Camera::GetProjectionMatrix(int CameraNum)
	{
		return projMatrix_[CameraNum];
	}
	XMMATRIX Camera::GetProjectionMatrix()
	{
		return projMatrix_[NULL];
	}
}