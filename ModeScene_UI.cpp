#include "ModeScene_UI.h"
#include "Engine/Picture.h"
#include "Storage.h"

ModeScene_UI::ModeScene_UI(GameObject* parent)
	: GameObject(parent, "ModeScene_UI")
{
	hPict_.clear();
}

ModeScene_UI::~ModeScene_UI()
{
}

void ModeScene_UI::Initialize()
{
	int pict = Picture::Load("Assets\\Button_Easy.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	pict = Picture::Load("Assets\\Button_Hard.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	transform_.scale_ = { 0.25f, 0.25f,0.25f };
	transform_.position_.y = 0.25f;
	Picture::SetTransform(hPict_.at((int)Difficulty::EASY), transform_);
	transform_.position_.y = -0.5f;
	Picture::SetTransform(hPict_.at((int)Difficulty::HARD), transform_);
}

void ModeScene_UI::Update()
{
}

void ModeScene_UI::Draw()
{
	for (int i = 0; i < hPict_.size(); i++)
	{
		Picture::Draw(hPict_.at(i));
	}
}

void ModeScene_UI::Release()
{
}