#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"
#include <memory>

class Text;

class SettingsScene_UI : public MouseOperationUI
{
	std::unique_ptr<Text> pText_;

	std::vector<int> hPict_;							//���[�h�����摜�̔z��
public:
	SettingsScene_UI(GameObject* parent);
	~SettingsScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void Draw() override;

	void Release() override;
};