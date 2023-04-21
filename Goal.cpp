#include "Goal.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"
#include "Judge.h"
#include "Player.h"
#include "SceneList.h"
#include "Screen_Puzzle.h"

Goal::Goal(GameObject* parent)
	: GameObject(parent, "Goal"), hModel_(-1), RayHit_(false), IsMouse_(), UVPosition_(), pPlayer_(nullptr)
{
}

Goal::~Goal()
{
}

void Goal::Initialize()
{
	hModel_ = Model::Load("Assets\\Key.fbx");
	assert(hModel_ >= 0);
	pPlayer_ = (Player*)GetParent()->GetParent();
}

void Goal::Update()
{
	if (pPlayer_->GetGoal())
	{
		float dist = MakeMouseRay();

		//カメラより手前にあるドアには当たらないようにする
		//マウスを押したタイミングで対象を指しているか
		if (RayHit_ && Input::Mouse::Down(0) && dist > 1.0f)
		{
			IsMouse_[0] = true;
		}
		//マウスを離したタイミングで対象を指しているか
		if (RayHit_ && Input::Mouse::Up(0) && dist > 1.0f)
		{
			IsMouse_[1] = true;
		}

		//両方trueならば呼び出す
		if (IsMouse_[0] && IsMouse_[1])
		{
			IsMouse_[0] = false;
			IsMouse_[1] = false;
			Judge::calculation();
			SCENE_CHANGE(SCENE_ID::CLEAR);
		}

		//押していなければfalseになる
		if (!Input::Mouse::IsPush(0))
		{
			IsMouse_[0] = false;
			IsMouse_[1] = false;
		}
	}
}

void Goal::Draw()
{
	if (pPlayer_->GetGoal())
	{
		Model::SetTransform(hModel_, transform_);

		if (RayHit_)
		{
			const XMFLOAT3 Chroma{ 1.0f, 1.0f, 1.0f };
			Model::Draw(hModel_, Chroma, UCHAR_MAX);
		}
		else
		{
			Model::Draw(hModel_);
		}
	}
}

void Goal::InitialPosition(char pos)
{
	UVPosition_ = XMFLOAT2((char)(pos / BoardSize_), (char)(pos % BoardSize_));
}

float Goal::MakeMouseRay()
{
	//マウス位置
	XMFLOAT3 mousePosFront = Input::Mouse::GetPosition();
	mousePosFront.x = mousePosFront.x;
	mousePosFront.z = 0;

	XMVECTOR front = SetInvMat(mousePosFront);

	XMFLOAT3 mousePosBack = Input::Mouse::GetPosition();
	mousePosBack.x = mousePosBack.x;
	mousePosBack.z = 1.0f;

	XMVECTOR back = SetInvMat(mousePosBack);

	XMVECTOR ray = back - front;
	ray = XMVector3Normalize(ray);

	RayCastData data;

	XMStoreFloat3(&data.start, front);
	XMStoreFloat3(&data.dir, ray);

	Model::SetTransform(hModel_, transform_);
	Model::RayCast(hModel_, data);

	RayHit_ = data.hit;

	return data.dist;
}

XMVECTOR Goal::SetInvMat(XMFLOAT3 pos)
{
	//ビューポート行列
	float w = 0;
	switch (Direct3D::SplitScrMode)
	{
	case SCREEN_MODE::FULL: w = (float)Direct3D::scrWidth / 2.0f; break;
	case SCREEN_MODE::SPLIT_2: w = (float)Direct3D::scrWidth / 4.0f; break;
	default: break;
	}
	float h = (float)Direct3D::scrHeight / 2.0f;
	XMMATRIX vp =
	{
		w, 0, 0, 0,
		0,-h, 0, 0,
		0, 0, 1, 0,
		w, h, 0, 1
	};

	//各行列の逆行列
	XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

	XMVECTOR vPos = XMLoadFloat3(&pos);

	XMMATRIX mat = invVp * invPrj * invView;

	vPos = XMVector3TransformCoord(vPos, mat);

	return vPos;
}

void Goal::SetUVPos(XMFLOAT2 move)
{
	UVPosition_ = XMFLOAT2(UVPosition_.x + move.x, UVPosition_.y + move.y);
}