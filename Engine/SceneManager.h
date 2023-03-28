#pragma once
#include "../../IntegratedEngine/Engine/GameObject.h"

enum class SCENE_ID
{
	MODE = 0,
	SETTINGS,
	PLAY,
	CLEAR
};

class SceneManager : public GameObject
{
	SCENE_ID CurrentSceneID_;
	SCENE_ID NextSceneID_;
public:
	SceneManager(GameObject* parent);
	~SceneManager();

	void Initialize() override;
	void Update() override;

	void ChangeScene(SCENE_ID ID) { NextSceneID_ = ID; }
};