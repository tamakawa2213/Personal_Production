#pragma once
#include "Engine/GameObject.h"
#include <vector>

class PlayScene_Menu : public GameObject
{
	std::vector<int> hPict_;
public:
	PlayScene_Menu(GameObject* parent);

	~PlayScene_Menu();

	void Initialize() override;

	void FixedUpdate() override;

	void DrawUnique() override;

	void Release() override;
};