#include "SettingScene.h"
#include "SettingScene_UI.h"

SettingScene::SettingScene(GameObject* parent)
	: GameObject(parent, "SettingScene")
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Initialize()
{
	Instantiate<SettingsScene_UI>(this);
}

void SettingScene::Update()
{
}

void SettingScene::Release()
{
}
