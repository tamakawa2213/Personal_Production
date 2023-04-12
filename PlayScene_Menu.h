#pragma once
#include "../IntegratedEngine/Engine/UserInterface.h"
#include <vector>

class PlayScene_Menu : public UserInterface
{
	std::vector<int> hPict_;
public:
	PlayScene_Menu();

	~PlayScene_Menu();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};