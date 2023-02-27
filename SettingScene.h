#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class SettingScene : public GameObject
{
public:
	SettingScene(GameObject* parent);
	~SettingScene();

	void Initialize() override;

	void Update() override;

	void Release() override;
};

