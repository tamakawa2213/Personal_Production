#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include <vector>

class ModeScene_UI : public GameObject
{
	enum class Pictlist
	{
		EASY = 0,
		HARD,
		SETTINGS
	};

	std::vector<int> hPict_;
public:
	ModeScene_UI(GameObject* parent);

	~ModeScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};