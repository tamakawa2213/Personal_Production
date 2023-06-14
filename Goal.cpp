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
	pPlayer_ = (Player*)FindObject("Player");
}

void Goal::Update()
{
	if (pPlayer_->IsGoal())
	{
		RayCastData data;
		data.CreateMouseRay();
		Model::SetTransform(hModel_, transform_);
		Model::RayCast(hModel_, data);

		RayHit_ = data.hit;

		//カメラより手前にあるドアには当たらないようにする
		//マウスを押したタイミングで対象を指しているか
		if (RayHit_ && Input::Mouse::Down(0) && data.dist > 1.0f)
		{
			IsMouse_[0] = true;
		}
		//マウスを離したタイミングで対象を指しているか
		if (RayHit_ && Input::Mouse::Up(0) && data.dist > 1.0f)
		{
			IsMouse_[1] = true;
		}

		//両方trueならば呼び出す
		if (IsMouse_[0] && IsMouse_[1])
		{
			IsMouse_[0] = false;
			IsMouse_[1] = false;
			KillMe();
			/*Judge::calculation();
			SCENE_CHANGE(SCENE_ID::CLEAR);*/
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
	if (pPlayer_->IsGoal())
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

void Goal::SetUVPos(XMFLOAT2 move)
{
	UVPosition_ = XMFLOAT2(UVPosition_.x + move.x, UVPosition_.y + move.y);
}