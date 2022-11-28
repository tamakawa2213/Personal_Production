#include "Screen_Room.h"
#include "Door.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Goal.h"

Screen_Room::Screen_Room(GameObject* parent)
	: IDObject(parent, "Screen_Room"), hModel_(), PrevPosX_(NULL), PrevPosY_(NULL), RoomType_(0), pDoor()
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
	std::string Filename[Room_MAX] = { "Room_HLt" ,"Room_HR" , "Room_LwLt" , "Room_LwR" , "Room_LtR" };
	for (int i = NULL; i < Room_MAX; i++)
	{
		std::string Name = "Assets\\" + Filename[i] + ".fbx";
		hModel_[i] = Model::Load(Name);
		assert(hModel_ >= NULL);
	}

	//2つのドアを作成
	pDoor[0] = Instantiate<Door>(this);
	pDoor[1] = Instantiate<Door>(this);

	Instantiate<Goal>(this);

	MoveOther(RoomType_);
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

	int Num = NULL;
	char PosNum = POSITION_MAX;

	while (Num < DoorNum || PosNum >= NULL)
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