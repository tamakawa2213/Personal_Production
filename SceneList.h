#pragma once
#include "../IntegratedEngine/Engine/Scene.h"

enum class SCENE_ID : int
{
	MODE = 0,
	SETTINGS,
	PLAY,
	CLEAR
};

class SceneList : public Scene
{
public:
	SceneList();
	~SceneList() {}

	void Initialize() override;

	void Update() override;
};

