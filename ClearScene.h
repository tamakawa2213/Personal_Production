#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class ClearScene : public GameObject
{
public:
	ClearScene(GameObject* parent);

	~ClearScene();

	void Initialize() override;

	void Update() override;

	void Release() override;
};