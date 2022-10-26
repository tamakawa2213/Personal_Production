#include "Screen_Room.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Screen_Room::Screen_Room(GameObject* parent)
	: GameObject(parent, "Screen_Room"), hModel_()
{
	transform_.position_ = XMFLOAT3(-1.0f, 4.0f, 1.5f);
	transform_.rotate_.x = 90;
	float scale = 0.2f;
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
}

void Screen_Room::Update()
{
}

void Screen_Room::Draw()
{
	int type = 2;
	Model::SetTransform(hModel_[type], transform_);
	Model::Draw(hModel_[type]);
}

void Screen_Room::Release()
{
}
