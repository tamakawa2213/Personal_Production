#include "Screen_Room.h"
#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Goal.h"
#include "Judge.h"
#include "Player.h"

//定数宣言
namespace
{
	enum class POSITION
	{
		HIGH = 0,
		LOW,
		LEFT,
		RIGHT,
		MAX
	};

	static const char POSITION[(char)POSITION::MAX] = { 0x01 << 3, 0x01 << 2, 0x01 << 1, 0x01 << 0 };

	//H = 8, Lw = 4, Lt = 2, R = 1
	//ドアの配置
	const char DoorConfig[] =
	{ POSITION[(char)POSITION::HIGH] | POSITION[(char)POSITION::LEFT] ,
	  POSITION[(char)POSITION::HIGH] | POSITION[(char)POSITION::RIGHT] ,
	  POSITION[(char)POSITION::LOW] | POSITION[(char)POSITION::LEFT] ,
	  POSITION[(char)POSITION::LOW] | POSITION[(char)POSITION::RIGHT] ,
	  POSITION[(char)POSITION::LEFT] | POSITION[(char)POSITION::RIGHT]};


	//ドアの位置
	const XMFLOAT3 DoorPos[(char)POSITION::MAX] =
	{
		XMFLOAT3(0, 0, 12.5f),
		XMFLOAT3(0, 0, -12.5f),
		XMFLOAT3(-12.5f, 0, 0),
		XMFLOAT3(12.5f, 0, 0)
	};
}

Screen_Room::Screen_Room(GameObject* parent)
	: IDObject(parent, "Screen_Room"), hModel_(-1), PrevPosX_(0), PrevPosY_(0), RoomType_(0), pDoor()
{
	transform_.position_ = XMFLOAT3(-10.0f, 4.5f, 1.5f);
	transform_.rotate_.x = 90;
	float scale = 0.3f;
	transform_.scale_ = scale;
}

Screen_Room::~Screen_Room()
{
}

void Screen_Room::Initialize()
{
	MLoad(hModel_, "Assets\\Room.fbx");

	//2つのドアを作成
	pDoor[0] = Instantiate<Door>(this);
	pDoor[1] = Instantiate<Door>(this);

	Instantiate<Goal>(this);

	Player* pPlayer = (Player*)GetParent();
	MoveOther(pPlayer->GetID());
	SAFE_RELEASE(pPlayer);
}

void Screen_Room::Update()
{
	switch (Direct3D::SplitScrMode)
	{
	case SCREEN_MODE::FULL:
		if (Input::Mouse::IsPush(0))
		{
			Look_Around();
		}
		break;
	case SCREEN_MODE::SPLIT_2:
		//画面左にマウスがある場合にのみ呼び出す
		if (Input::Mouse::IsPush(0) && Input::Mouse::GetPosition().x < Direct3D::scrWidth / 2)
		{
			Look_Around();
		}
	default:
		break;
	}
}

void Screen_Room::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Screen_Room::Release()
{
}

void Screen_Room::MoveOther(char Type)
{
	RoomType_ = Type;

	int Num = 0;
	char PosNum = (char)POSITION::MAX;

	while (Num < DoorNum && PosNum >= 0)
	{
		PosNum--;

		//部屋のタイプに合致したドアの配置にする
		if (DoorConfig[Type] & POSITION[PosNum])
		{
			pDoor[Num]->SetPosition(DoorPos[PosNum]);
			pDoor[Num]->SetID(PosNum);
			Num++;
		}
	}

	Player* pPlayer = (Player*)GetParent();
	Goal* pGoal = (Goal*)FindChildObject("Goal");
	pPlayer->SetGoal((pPlayer->GetUVPos().x == pGoal->GetUVPos().x) && (pPlayer->GetUVPos().y == pGoal->GetUVPos().y));
	SAFE_RELEASE(pGoal);
	SAFE_RELEASE(pPlayer);

	Judge::AddNom();	//手数を1加算
}

void Screen_Room::Look_Around()
{
	if (Input::Mouse::Down(0))	//初期化
	{
		PrevPosX_ = (short)Input::Mouse::GetPosition().x;
		PrevPosY_ = (short)Input::Mouse::GetPosition().y;
	}

	float moveX;
	moveX = (Input::Mouse::GetPosition().x - PrevPosX_) / 2;

	transform_.rotate_.z += moveX;

	PrevPosX_ = (short)Input::Mouse::GetPosition().x;
	PrevPosY_ = (short)Input::Mouse::GetPosition().y;
}