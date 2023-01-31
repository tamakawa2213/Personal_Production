#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include "../IntegratedEngine/Engine/Text.h"

class ModeScene : public GameObject
{
	//Text* pText_;
public:
	ModeScene(GameObject* parent);

	~ModeScene();

	void Initialize() override;

	void Update() override;

	void Release() override;

	void Draw() override;
};