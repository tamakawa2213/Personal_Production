#include "Screen_Room.h"
#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Goal.h"
#include "Judge.h"
#include "Player.h"

//�萔�錾
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
	//�h�A�̔z�u
	const char DoorConfig[] =
	{ POSITION[(char)Position::HIGH] | POSITION[(char)Position::LEFT] ,
	  POSITION[(char)Position::HIGH] | POSITION[(char)Position::RIGHT] ,
	  POSITION[(char)Position::LOW] | POSITION[(char)Position::LEFT] ,
	  POSITION[(char)Position::LOW] | POSITION[(char)Position::RIGHT] ,
	  POSITION[(char)Position::LEFT] | POSITION[(char)Position::RIGHT]};


	//�h�A�̈ʒu
	const XMFLOAT3 DoorPos[(char)Position::MAX] =
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
	transform_.scale_ = XMFLOAT3(scale, scale, scale);
}

Screen_Room::~Screen_Room()
{
}

void Screen_Room::Initialize()
{
	MLoad(hModel_, "Assets\\Room.fbx");

	//2�̃h�A���쐬
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
	case SCREEN_FULL:
		if (Input::IsMouse(0))
		{
			Look_Around();
		}
		break;
	case SCREEN_SPLIT_2:
		//��ʍ��Ƀ}�E�X������ꍇ�ɂ̂݌Ăяo��
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
	char PosNum = (char)Position::MAX;

	while (Num < DoorNum && PosNum >= 0)
	{
		PosNum--;

		//�����̃^�C�v�ɍ��v�����h�A�̔z�u�ɂ���
		if (DoorConfig[Type] & POSITION[PosNum])
		{
			pDoor[Num]->SetPosition(DoorPos[PosNum]);
			pDoor[Num]->SetID(PosNum);
			Num++;
		}
	}
	Judge::AddNom();	//�萔��1���Z
}

void Screen_Room::Look_Around()
{
	if (Input::IsMouseDown(0))	//������
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