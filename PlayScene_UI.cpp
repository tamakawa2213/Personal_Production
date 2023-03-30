#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Gametime.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "PlayScene_Menu.h"

PlayScene_UI::PlayScene_UI(GameObject* parent)
	: MouseOperationUI(parent, "PlayScene_UI"), hPict_(-1)
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

void PlayScene_UI::ClickLeftFirst()
{
	if (Image::IsHitCursor(hPict_))
	{
		//���j���[�I�u�W�F�N�g��{��
		auto pMenu = FindObject("PlayScene_Menu");

		//�I�u�W�F�N�g������ = ���j���[���J���Ă���
		if (pMenu)
		{
			//���j���[�����
			pMenu->KillMe();

			GameTime::TimeStart();
			Time::UnLock();
		}
		else
		{
			//���j���[���J��
			Instantiate<PlayScene_Menu>(GetParent());
		}

		SAFE_RELEASE(pMenu);
	}
}

void PlayScene_UI::DrawUnique()
{
	Image::Draw(hPict_);
}

void PlayScene_UI::Release()
{
}
