#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class ModeScene : public GameObject
{
public:
	ModeScene(GameObject* parent);

	~ModeScene();

	void Initialize() override;

	void Update() override;

	void Release() override;

	void Draw() override;
};