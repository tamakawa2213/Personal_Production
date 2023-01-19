#include "PlayScene_Menu.h"
#include "Engine/Input.h"
#include "Engine/GameTime.h"
#include "Engine/Picture.h"
#include "Engine/SceneManager.h"
#include "Engine/Time.h"

PlayScene_Menu::PlayScene_Menu(GameObject* parent)
	: GameObject(parent, "PlayScene_Menu")
{
	hPict_.clear();
}

PlayScene_Menu::~PlayScene_Menu()
{
	hPict_.clear();
}

void PlayScene_Menu::Initialize()
{
	int pict = Picture::Load("Assets\\ToDifficulty.png");
	assert(pict >= 0);
	hPict_.push_back(pict);
	pict = Picture::Load("Assets\\Return.png");
	hPict_.push_back(pict);

	transform_.position_ = { -0.4f, -0.3f,0 };
	Picture::SetTransform(hPict_.at(0), transform_);

	transform_.position_.x = 0.4f;
	Picture::SetTransform(hPict_.at(1), transform_);

	GameTime::TimeStop();
	Time::Lock();
}

void PlayScene_Menu::FixedUpdate()
{
	if (Input::IsMouseDown(0))
	{
		if (Picture::IsHitCursor(hPict_.at(0)))
		{
			SCENE_CHANGE(SCENE_ID_MODE);
			GameTime::TimeStart();
		}
		if (Picture::IsHitCursor(hPict_.at(1)))
		{
			Time::UnLock();
			GameTime::TimeStart();
			KillMe();
		}
	}
}

void PlayScene_Menu::DrawUnique()
{
	for (auto p : hPict_)
	{
		Picture::Draw(p);
	}
}

void PlayScene_Menu::Release()
{
}