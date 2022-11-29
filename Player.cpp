#include "Player.h"
#include "Screen_Puzzle.h"
#include "Screen_Room.h"

Player::Player(GameObject* parent)
	: IDObject(parent, "Player"), UVPosition_(), Wait_(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	//èâä˙à íuÇ∆IDÇéwíË
	SetID(rand() % Board_MAX);
	char pos = rand() % 16;
	UVPosition_ = XMFLOAT2((char)(pos / BoardSize_), (char)(pos % BoardSize_));

	Instantiate<Screen_Room>(this);
	Instantiate<Screen_Puzzle>(this);
}

void Player::Update()
{
}

void Player::Release()
{
}

void Player::ReceiveFromDoor()
{
	Screen_Puzzle* pSP = (Screen_Puzzle*)FindChildObject("Screen_Puzzle");
	char path = pSP->SendToken(UVPosition_, this->GetID());

	if (path != Board_MAX)
	{
		Screen_Room* pSR = (Screen_Room*)FindChildObject("Screen_Room");
		pSR->MoveOther(path);
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
