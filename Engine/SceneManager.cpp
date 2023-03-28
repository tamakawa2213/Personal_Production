#include "SceneManager.h"
#include "../../IntegratedEngine/Engine/Model.h"
#include "../../IntegratedEngine/Engine/Image.h"
#include "../ModeScene.h"
#include "../PlayScene.h"
#include "../ClearScene.h"
#include "../SettingScene.h"

SceneManager::SceneManager(GameObject* parent) : GameObject(parent, "SceneManager")
{
	CurrentSceneID_ = SCENE_ID::MODE;
	NextSceneID_ = CurrentSceneID_;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	Instantiate<ModeScene>(this);
}

void SceneManager::Update()
{
	if (CurrentSceneID_ != NextSceneID_)
	{
		KillAllChildren();
		Model::Release();
		Image::Release();

		//‰æ–Ê‚Ì–¾‚é‚³‚ðŒ³‚É–ß‚·
		assFunc_.SetFadeout(1);

		switch (NextSceneID_)
		{
		case SCENE_ID::MODE: Instantiate<ModeScene>(this); break;
		case SCENE_ID::SETTINGS: Instantiate<SettingScene>(this); break;
		case SCENE_ID::PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID::CLEAR: Instantiate<ClearScene>(this); break;
		}

		CurrentSceneID_ = NextSceneID_;
	}
	
}
