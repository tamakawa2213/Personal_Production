#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Gametime.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "PlayScene_Menu.h"

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
	int pict = Image::Load("Assets\\Button_Menu.png");
	assert(pict >= 0);

	hPict_.push_back(pict);
}

void PlayScene_UI::FixedUpdate()
{
	if (Input::IsMouseDown(0) && Image::IsHitCursor(hPict_.at(0)))
	{
		//メニューオブジェクトを捜索
		auto pMenu = FindObject("PlayScene_Menu");

		//オブジェクトがある = メニューを開いている
		if (pMenu)
		{
			//メニューを閉じる
			pMenu->KillMe();

			GameTime::TimeStart();
			Time::UnLock();
		}
		else
		{
			//メニューを開く
			Instantiate<PlayScene_Menu>(GetParent());
		}

		SAFE_RELEASE(pMenu);
	}
}

void PlayScene_UI::DrawUnique()
{
	Image::Draw(hPict_.at(0));
}

void PlayScene_UI::Release()
{
}
