#include "SettingScene.h"
#include "SettingScene_UI.h"
#include "../IntegratedEngine/Engine/RootUI.h"

SettingScene::SettingScene(GameObject* parent)
	: GameObject(parent, "SettingScene")
{
}

SettingScene::~SettingScene()
{
}

void SettingScene::Initialize()
{
	SET_UI(SettingsScene_UI);
}

void SettingScene::Update()
{
}

void SettingScene::Release()
{
}
