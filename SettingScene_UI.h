#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"

class Text;

class SettingsScene_UI : public MouseOperationUI
{
	Text* pText_;

	std::vector<int> hPict_;							//���[�h�����摜�̔z��
public:
	SettingsScene_UI(GameObject* parent);
	~SettingsScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void Draw() override;

	void Release() override;
};