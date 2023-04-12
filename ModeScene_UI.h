#pragma once
#include "../IntegratedEngine/Engine/UserInterface.h"
#include <map>
#include <vector>

class ModeScene_UI : public UserInterface
{
	std::vector<int> hPict_;						//���[�h�����摜�̔z��
	std::map<int, void(ModeScene_UI::*)()> Func_;	//�摜�Ɗ֐��̘A�z�z��

	void SelectEasy();		//easy�{�^���������������̏���
	void SelectHard();		//hard			�V
	void SelectSettings();	//�ݒ�			�V
public:
	ModeScene_UI();

	~ModeScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};