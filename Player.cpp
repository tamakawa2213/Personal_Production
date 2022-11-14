#include "Player.h"
#include "Door.h"
#include "Screen_Puzzle.h"
#include "Screen_Room.h"

Player::Player(GameObject* parent)
	: IDObject(parent, "Player"), UVPosition_()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	Instantiate<Screen_Puzzle>(this);
	Instantiate<Screen_Room>(this);
	UVPosition_ = { 0,0 };
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
		Door* pDoor = (Door*)FindObject("Door");
		int i = 0;
	}
}
