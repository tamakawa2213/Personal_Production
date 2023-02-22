#include "Player.h"
#include "Screen_Puzzle.h"
#include "Screen_Room.h"
#include "../IntegratedEngine/Engine/Direct3D.h"

Player::Player(GameObject* parent)
	: IDObject(parent, "Player"), UVPosition_(), Wait_(false), MoveRoom_(false), DoorPath_(-1), pSR(nullptr), pSP(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//初期位置とIDを指定
	SetID(rand() % (char)Board::MAX);
	char pos = rand() % 16;
	UVPosition_ = XMFLOAT2((char)(pos / BoardSize_), (char)(pos % BoardSize_));

	pSR = Instantiate<Screen_Room>(this);
	pSP = Instantiate<Screen_Puzzle>(this);
}

void Player::Update()
{
	if (MoveRoom_)
	{
		assFunc_.SetFadeout(150);
		MoveRoom_ = false;
	}

	if (Wait_ && Direct3D::BackGroundColor[1] < 0.1f)
	{
		pSR->MoveOther(DoorPath_);
		Wait_ = false;
	}
}

void Player::Release()
{
	SAFE_RELEASE(pSP);
	SAFE_RELEASE(pSR);
}

void Player::ReceiveFromDoor()
{
	//ドアが繋がっているか確認
	DoorPath_ = pSP->SendToken(UVPosition_, this->GetID());

	if (DoorPath_ != (char)Board::MAX)
	{
		Wait_ = true;
		MoveRoom_ = true;
	}
}

void Player::SetUVPos(XMFLOAT2 move)
{
	UVPosition_ = XMFLOAT2(UVPosition_.x + move.x, UVPosition_.y + move.y);
}

void Player::SetWait(bool wait)
{
	Wait_ = wait;
}
