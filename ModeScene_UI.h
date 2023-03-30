#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"
#include <map>

class ModeScene_UI : public MouseOperationUI
{
	std::vector<int> hPict_;						//���[�h�����摜�̔z��
	std::map<int, void(ModeScene_UI::*)()> Func_;	//�摜�Ɗ֐��̘A�z�z��

	void SelectEasy();		//easy�{�^���������������̏���
	void SelectHard();		//hard			�V
	void SelectSettings();	//�ݒ�			�V
public:
	ModeScene_UI(GameObject* parent);

	~ModeScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void Draw() override;

	void Release() override;
};