#pragma once
#include "../IntegratedEngine/Engine/RootUI.h"

class Text;

class SettingsScene_UI : public UserInterface
{
	std::unique_ptr<Text> pText_;

	std::vector<int> hPict_;							//ƒ[ƒh‚µ‚½‰æ‘œ‚Ì”z—ñ
public:
	SettingsScene_UI(RootUI* ui);
	~SettingsScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};