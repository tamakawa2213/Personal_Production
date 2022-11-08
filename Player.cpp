#include "Player.h"
#include "Screen_Puzzle.h"
#include "Screen_Room.h"

Player::Player(GameObject* parent)
	: GameObject(parent, "Player")
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	Instantiate<Screen_Puzzle>(this);
	Instantiate<Screen_Room>(this);
}

void Player::Update()
{
}

void Player::Release()
{
}