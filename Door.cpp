#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Player.h"

Door::Door(GameObject* parent)
	: IDObject(parent, "Door"), hModel_(-1), RayHit_(false), IsMouse_()
{
}

Door::~Door()
{
}

void Door::Initialize()
{
	hModel_ = Model::Load("Assets\\Door.fbx");
	assert(hModel_ >= 0);
}

void Door::Update()
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
		//ドアをクリックしたらPlayerにIDを送る
		SendtoPlayer();
		IsMouse_[0] = false;
		IsMouse_[1] = false;
	}

	//押していなければfalseになる
	if (!Input::Mouse::IsPush(0))
	{
		IsMouse_[0] = false;
		IsMouse_[1] = false;
	}
}

void Door::Draw()
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

void Door::SendtoPlayer()
{
	Player* pPlayer;
	pPlayer = (Player*)GetParent()->GetParent();	//親オブジェクトの親オブジェクトがPlayer
	if (!pPlayer->GetWait())						//待機状態かどうか
	{
		pPlayer->SetID(this->GetID());				//自分自身のIDを送る
		pPlayer->ReceiveFromDoor();
	}
}