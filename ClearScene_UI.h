#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class ClearScene_UI : public GameObject
{
	int hPict_;
public:
	ClearScene_UI(GameObject* parent);

	~ClearScene_UI();

	void Initialize() override;

	void FixedUpdate() override;

	void DrawUnique() override;

	void Release() override;
};