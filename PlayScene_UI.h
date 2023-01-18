#pragma once
#include "Engine/GameObject.h"
#include <vector>

class PlayScene_UI : public GameObject
{
	std::vector<int> hPict_;
public:
	PlayScene_UI(GameObject* parent);

	~PlayScene_UI();

	void Initialize() override;

	void Update() override;

	void DrawUnique() override;

	void Release() override;
};