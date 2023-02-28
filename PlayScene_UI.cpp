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
	Image::Draw(hPict_.at(0));
}

void PlayScene_UI::Release()
{
}
