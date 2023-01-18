#include "PlayScene_UI.h"
#include "Engine/Picture.h"
#include "Engine/Input.h"
#include "Engine/GameTime.h"
#include "Engine/Time.h"

PlayScene_UI::PlayScene_UI(GameObject* parent)
	: GameObject(parent, "PlayScene_UI")
{
	hPict_.clear();
}

PlayScene_UI::~PlayScene_UI()
{
}

void PlayScene_UI::Initialize()
{
	int pict = Picture::Load("Assets\\Button_Menu.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	transform_.scale_ = { 0.25f, 0.25f,0.25f };
	transform_.position_ = { -0.7f, 0.8f, 0 };
	Picture::SetTransform(hPict_.at(0), transform_);
}

void PlayScene_UI::Update()
{
	if (Input::IsMouseDown(0) && Picture::IsHitCursor(hPict_.at(0)))
	{
		GameTime::TimeStop();
		Time::Lock();
	}
}

void PlayScene_UI::DrawUnique()
{
	for (int i = 0; i < hPict_.size(); i++)
	{
		Picture::Draw(hPict_.at(i));
	}
}

void PlayScene_UI::Release()
{
}
