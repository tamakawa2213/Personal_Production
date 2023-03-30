#include "SettingScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Text.h"
#include "Engine/SceneManager.h"
#include "Storage.h"

SettingsScene_UI::SettingsScene_UI(GameObject* parent)
	: MouseOperationUI(parent, "SettingScene_UI"), pText_(nullptr), hPict_()
{
}

SettingsScene_UI::~SettingsScene_UI()
{
	hPict_.clear();
}

void SettingsScene_UI::Initialize()
{
	FontData* data = new FontData();
	data->fontSize = 5;
	pText_ = new Text(data);
	pText_->Initialize();
	SAFE_DELETE(data);

	int pic;
	ILoad(pic, "Assets\\Fadeout_slow.png");

	hPict_.push_back(pic);

	ILoad(pic, "Assets\\Fadeout_normal.png");

	hPict_.push_back(pic);

	ILoad(pic, "Assets\\Fadeout_fast.png");

	hPict_.push_back(pic);

	ILoad(pic, "Assets\\Sample.png");

	hPict_.push_back(pic);

	ILoad(pic, "Assets\\Turnback.png");

	hPict_.push_back(pic);
}

void SettingsScene_UI::ClickLeftFirst()
{
	int choice = Image::IsHitCursorAny();
	switch (choice)
	{
	case 0:
	case 1:
	case 2:
		Storage::SetFadeoutMode(choice);
		break;
	case 3:
		assFunc_.SetFadeout(Storage::GetFadeoutSpeed());
		break;
	case 4:
	{
		SCENE_CHANGE(SCENE_ID::MODE);
		break;
	}
	default:
		break;
	}
}

void SettingsScene_UI::Draw()
{
	pText_->Draw({ 0, 15 }, "フェードアウトのスピード");

	for (int i : hPict_)
	{
		Image::Draw(hPict_.at(i));
	}
}

void SettingsScene_UI::Release()
{
}
