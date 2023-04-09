#pragma once
#include "../IntegratedEngine/Engine/Scene.h"

enum class SCENE_ID
{
	MODE = 0,
	SETTINGS,
	PLAY,
	CLEAR
};

class SceneList : public Scene
{
public:
	SceneList() : Scene() {}
	~SceneList() {}

	void Initialize();

	void Update();
};

