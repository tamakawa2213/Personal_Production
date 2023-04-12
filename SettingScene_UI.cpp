#include "SettingScene_UI.h"
#include "../IntegratedEngine/Engine/CallDef.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"
#include "../IntegratedEngine/Engine/Text.h"
#include "Storage.h"
#include "SceneList.h"

SettingsScene_UI::SettingsScene_UI()
	: UserInterface(), pText_(nullptr), hPict_()
{
}

SettingsScene_UI::~SettingsScene_UI()
{
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

void SettingsScene_UI::Update()
{
	if (Input::Mouse::Down(0))
	{
		switch (int choice = Image::IsHitCursorAny(); choice)
		{
		case 0:
		case 1:
		case 2:
			Storage::SetFadeoutMode(choice);
			break;
		case 3:
			PtrObserver::GetSceneManager()->assFunc_.SetFadeout(Storage::GetFadeoutSpeed());
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
}

void SettingsScene_UI::Draw()
{
	if(pText_)
	pText_->Draw({ 0, 15 }, "フェードアウトのスピード");

	for (auto&& itr : hPict_)
	{
		Image::Draw(itr);
	}
}

void SettingsScene_UI::Release()
{
	pText_->Release();
	hPict_.clear();
}
