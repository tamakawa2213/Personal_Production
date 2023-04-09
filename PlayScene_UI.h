#pragma once
#include "../IntegratedEngine/Engine/RootUI.h"

class PlayScene_UI : public UserInterface
{
	int hPict_;
public:
	PlayScene_UI(RootUI* ui);

	~PlayScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};