#include "PlayScene_Menu.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/GameTime.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "Engine/SceneManager.h"
#include "../IntegratedEngine/Engine/Time.h"

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
	int pict;
	ILoad(pict, "Assets\\ToDifficulty.png");
	hPict_.push_back(pict);

	ILoad(pict, "Assets\\Return.png");
	hPict_.push_back(pict);

	GameTime::TimeStop();
	Time::Lock();
}

void PlayScene_Menu::FixedUpdate()
{
	if (Input::IsMouseDown(0))
	{
		if (Image::IsHitCursor(hPict_.at(0)))
		{
			SCENE_CHANGE(SCENE_ID_MODE);
			GameTime::TimeStart();
		}
		if (Image::IsHitCursor(hPict_.at(1)))
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
		Image::Draw(p);
	}
}

void PlayScene_Menu::Release()
{
}