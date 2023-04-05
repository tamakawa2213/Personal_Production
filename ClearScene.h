#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include <memory>

class Text;

class ClearScene : public GameObject
{
	std::unique_ptr<Text> pText_;
public:
	ClearScene(GameObject* parent);

	~ClearScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};