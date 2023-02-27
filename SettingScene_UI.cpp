#include "SettingScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Text.h"

SettingsScene_UI::SettingsScene_UI(GameObject* parent)
	: GameObject(parent, "SettingScene_UI"), pText_(nullptr), hPict_()
{
}

SettingsScene_UI::~SettingsScene_UI()
{
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
}

void SettingsScene_UI::Update()
{
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
