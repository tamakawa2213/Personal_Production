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
	std::unique_ptr<FontData> data = std::make_unique<FontData>();
	data->fontSize = 5;
	pText_ = std::make_unique<Text>(data.get());
	pText_->Initialize();

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
	switch (int choice = Image::IsHitCursorAny(); choice)
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
	pText_->Draw({ 0, 15 }, "�t�F�[�h�A�E�g�̃X�s�[�h");

	for (auto&& itr : hPict_)
	{
		Image::Draw(itr);
	}
}

void SettingsScene_UI::Release()
{
}
