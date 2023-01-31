#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class PlayScene : public GameObject
{
public:
	PlayScene(GameObject* parent);

	~PlayScene();

	void Initialize() override;

	void Update() override;

	void ShowGraphical() override;

	void Release() override;
};