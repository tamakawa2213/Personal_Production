#pragma once
#include "Engine/GameObject.h"
#include <vector>

class ModeScene_UI : public GameObject
{
	std::vector<int> hPict_;
public:
	ModeScene_UI(GameObject* parent);

	~ModeScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};