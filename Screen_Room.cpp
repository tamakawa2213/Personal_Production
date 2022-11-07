#include "Screen_Room.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include "Door.h"

Screen_Room::Screen_Room(GameObject* parent)
	: GameObject(parent, "Screen_Room"), hModel_(), PrevPosX_(NULL), PrevPosY_(NULL), RoomType_(NULL)
{
	transform_.position_ = XMFLOAT3(0.0f, 4.5f, 1.5f);
	transform_.rotate_.x = 90;
	float scale = 0.1f;
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
	MoveOther(NULL);
}

void Screen_Room::Update()
{
	if (Input::IsMouse(0))
	{
		Look_Around();
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
	KillAllChildren();

	Door* pDoor[DoorNum] = { Instantiate<Door>(this), Instantiate<Door>(this) };
	int Num = NULL;
	int PosNum = NULL;
	DoorPos Pos;

	while (PosNum < POSITION_MAX)
	{
		if (DoorConfig[Type] & POSITION[PosNum])
		{

		}
	}
}

void Screen_Room::Look_Around()
{
	if (Input::IsMouseDown(0))
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