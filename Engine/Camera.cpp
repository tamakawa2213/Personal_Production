#include "Camera.h"
#include "CallDef.h"

//変数
namespace Camera {
	XMVECTOR position_;	//カメラの位置（視点）
	XMVECTOR target_;	//見る位置（焦点）
	XMMATRIX viewMatrix_;	//ビュー行列
	XMMATRIX projMatrix_;	//プロジェクション行列


//初期化
	void Camera::Initialize()
	{
		position_ = XMVectorSet(1.5f, 5, -3, 0);	//カメラの位置
		target_ = XMVectorSet(1.5f, 0, 1.5f, 0);		//カメラの焦点
		projMatrix_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)800 / (FLOAT)600, 0.1f, 100.0f);	//プロジェクション行列
	}

	//更新
	void Camera::Update()
	{
		//ビュー行列の作成(カメラ固定のゲームならInitializeに書く)
		viewMatrix_ = XMMatrixLookAtLH(position_, target_, XMVectorSet(0, 1, 0, 0));
	}

	//位置を設定
	void Camera::SetPosition(XMVECTOR position)
	{
		position_ = position;
	}

	//焦点を設定
	void Camera::SetTarget(XMVECTOR target)
	{
		target_ = target;
	}

	//ビュー行列を取得
	XMMATRIX Camera::GetViewMatrix()
	{
		return viewMatrix_;
	}

	//プロジェクション行列を取得
	XMMATRIX Camera::GetProjectionMatrix()
	{
		return projMatrix_;
	}
}