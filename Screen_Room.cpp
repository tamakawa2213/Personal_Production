#include "Screen_Room.h"
#include "Door.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Goal.h"
#include "Player.h"

//定数宣言
namespace
{
	enum class Position
	{
		HIGH = 0,
		LOW,
		LEFT,
		RIGHT,
		MAX
	};

	static const char POSITION[(char)Position::MAX] = { 0x01 << 3, 0x01 << 2, 0x01 << 1, 0x01 << 0 };

	//H = 8, Lw = 4, Lt = 2, R = 1
	//ドアの配置
	const char DoorConfig[(char)Room::MAX] =
	{ POSITION[(char)Position::HIGH] | POSITION[(char)Position::LEFT] ,
	  POSITION[(char)Position::HIGH] | POSITION[(char)Position::RIGHT] ,
	  POSITION[(char)Position::LOW] | POSITION[(char)Position::LEFT] ,
	  POSITION[(char)Position::LOW] | POSITION[(char)Position::RIGHT] ,
	  POSITION[(char)Position::LEFT] | POSITION[(char)Position::RIGHT]};


	//ドアの位置
	const XMFLOAT3 DoorPos[(char)Position::MAX] =
	{
		XMFLOAT3(0, 0, -4.0f),
		XMFLOAT3(0, 0, 4.0f),
		XMFLOAT3(-4.0f, 0, 0),
		XMFLOAT3(4.0f, 0, 0)
	};
}

Screen_Room::Screen_Room(GameObject* parent)
	: IDObject(parent, "Screen_Room"), hModel_(), PrevPosX_(0), PrevPosY_(0), RoomType_(0), pDoor()
{
	transform_.position_ = XMFLOAT3(-10.0f, 4.5f, 1.5f);
	transform_.rotate_.x = 90;
	float scale = 0.3f;
	transform_.scale_ = XMFLOAT3(scale, scale, scale);
}

Screen_Room::~Screen_Room()
{
}

void Screen_Room::Initialize()
{
	std::string Filename[(char)Room::MAX] = { "Room_HLt" ,"Room_HR" , "Room_LwLt" , "Room_LwR" , "Room_LtR" };
	for (int i = 0; i < (char)Room::MAX; i++)
	{
		std::string Name = "Assets\\" + Filename[i] + ".fbx";
		hModel_[i] = Model::Load(Name);
		assert(hModel_ >= 0);
	}

	//2つのドアを作成
	pDoor[0] = Instantiate<Door>(this);
	pDoor[1] = Instantiate<Door>(this);

	Instantiate<Goal>(this);

	Player* pPlayer = (Player*)GetParent();
	MoveOther(pPlayer->GetID());
}

void Screen_Room::Update()
{
	switch (Direct3D::SplitScrMode)
	{
	case SCREEN_FULL:
		if (Input::IsMouse(0))
		{
			Look_Around();
		}
		break;
	case SCREEN_SPLIT_2:
		//画面左にマウスがある場合にのみ呼び出す
		if (Input::IsMouse(0) && Input::GetMousePosition().x < Direct3D::scrWidth / 2)
		{
			Look_Around();
		}
	default:
		break;
	}
}

void Screen_Room::Draw()
{
	Model::SetTransform(hModel_[RoomType_], transform_);
	Model::Draw(hModel_[RoomType_]);
}

void Screen_Room::Release()
{
}

void Screen_Room::MoveOther(char Type)
{
	RoomType_ = Type;

	int Num = 0;
	char PosNum = (char)Position::MAX;

	while (Num < DoorNum || PosNum >= 0)
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
}

void Screen_Room::Look_Around()
{
	if (Input::IsMouseDown(0))	//初期化
	{
		PrevPosX_ = (short)Input::GetMousePosition().x;
		PrevPosY_ = (short)Input::GetMousePosition().y;
	}

	float moveX;
	moveX = (Input::GetMousePosition().x - PrevPosX_) / 2;

	transform_.rotate_.z += moveX;

	PrevPosX_ = (short)Input::GetMousePosition().x;
	PrevPosY_ = (short)Input::GetMousePosition().y;
}