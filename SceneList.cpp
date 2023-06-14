#include "SceneList.h"
#include "ModeScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "SettingScene.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"

SceneList::SceneList()
	:Scene(SCENE_ID::MODE)
{
}

void SceneList::Initialize()
{
	ptr_ = PtrObserver::GetSceneManager();
	ptr_->Instantiate<ModeScene>(ptr_);
}

void SceneList::Update()
{
	switch (NextSceneID_)
	{
	case SCENE_ID::MODE: ptr_->Instantiate<ModeScene>(ptr_); break;
	case SCENE_ID::SETTINGS: ptr_->Instantiate<SettingScene>(ptr_); break;
	case SCENE_ID::PLAY: ptr_->Instantiate<PlayScene>(ptr_); break;
	case SCENE_ID::CLEAR: ptr_->Instantiate<ClearScene>(ptr_); break;

	default:break;
	}

	CurrentSceneID_ = NextSceneID_;
}
