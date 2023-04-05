#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"
#include <memory>

class Text;

class SettingsScene_UI : public MouseOperationUI
{
	std::unique_ptr<Text> pText_;

	std::vector<int> hPict_;							//ƒ[ƒh‚µ‚½‰æ‘œ‚Ì”z—ñ
public:
	SettingsScene_UI(GameObject* parent);
	~SettingsScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void Draw() override;

	void Release() override;
};