#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Gametime.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "PlayScene_Menu.h"

PlayScene_UI::PlayScene_UI(RootUI* ui)
	: UserInterface(ui), hPict_(-1)
{
}

PlayScene_UI::~PlayScene_UI()
{
}

void PlayScene_UI::Initialize()
{
	hPict_ = Image::Load("Assets\\Button_Menu.png");
	assert(hPict_ >= 0);
}

void PlayScene_UI::Update()
{
	if (Input::Mouse::Down(0) && Image::IsHitCursor(hPict_))
	{
		////オブジェクトがある = メニューを開いている
		//if (pMenu)
		//{
		//	//メニューを閉じる
		//	pMenu->KillMe();

		//	GameTime::TimeStart();
		//	Time::UnLock();
		//}
		//else
		//{
			//メニューを開く
			pRootUI_->Link<PlayScene_Menu>();
		//}
	}
}

void PlayScene_UI::Draw()
{
	Image::Draw(hPict_);
}

void PlayScene_UI::Release()
{
}
