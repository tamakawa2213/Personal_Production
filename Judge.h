#pragma once

class Goal;

namespace Judge
{
	void Initialize();	//������
	void AddNom();		//�萔�̉��Z
	int GetNom();
	void calculation();	//�X�R�A�̎Z�o
	int GetScore();		//�X�R�A���擾����

	//�N���A����������
	void JudgeClear();

	void AddGoal(Goal* g);
};