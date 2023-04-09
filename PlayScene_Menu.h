#pragma once
#include "../IntegratedEngine/Engine/RootUI.h"
#include <vector>

class PlayScene_Menu : public UserInterface
{
	std::vector<int> hPict_;
public:
	PlayScene_Menu(RootUI* ui);

	~PlayScene_Menu();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};