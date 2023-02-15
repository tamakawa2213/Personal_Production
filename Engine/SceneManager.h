#pragma once
#include "../../IntegratedEngine/Engine/GameObject.h"

enum SCENE_ID
{
	SCENE_ID_MODE = 0,
	SCENE_ID_PLAY,
	SCENE_ID_CLEAR
};

class SceneManager : public GameObject
{
	unsigned int CurrentSceneID_;
	unsigned int NextSceneID_;
public:
	SceneManager(GameObject* parent);
	~SceneManager();

	void Initialize() override;
	void Update() override;

	void DebugMode() override;

	void ChangeScene(unsigned int SCENE_ID) { NextSceneID_ = SCENE_ID; }
};