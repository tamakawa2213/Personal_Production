#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Gametime.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "PlayScene_Menu.h"

PlayScene_UI::PlayScene_UI(GameObject* parent)
	: GameObject(parent, "PlayScene_UI"), OpenMenu_(false)
{
	hPict_.clear();
}

PlayScene_UI::~PlayScene_UI()
{
}

void PlayScene_UI::Initialize()
{
	int pict = Image::Load("Assets\\Button_Menu.png");
	assert(pict >= 0);

	hPict_.push_back(pict);
}

void PlayScene_UI::FixedUpdate()
{
	if (Input::IsMouseDown(0) && Image::IsHitCursor(hPict_.at(0)))
	{
		if (OpenMenu_)
		{//メニューが表示されている時に再度メニューボタンを押下した時
			OpenMenu_ = false;
			FindObject("PlayScene_Menu")->KillMe();

			GameTime::TimeStart();
			Time::UnLock();
		}
		else
			OpenMenu_ = true;
	}

	if (OpenMenu_ && !FindObject("PlayScene_Menu"))
	{
		Instantiate<PlayScene_Menu>(GetParent());
	}
}

void PlayScene_UI::DrawUnique()
{
	Image::Draw(hPict_.at(0));
}

void PlayScene_UI::Release()
{
}
