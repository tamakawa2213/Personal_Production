#pragma once
#include "Engine/Model.h"
#include "Engine/GameObject.h"
#include "Screen_Puzzle.h"

class Goal : public GameObject
{
	int hModel_;
	bool RayHit_;						//���C���������Ă��邩�ǂ���

	bool IsMouse_[2];					//�}�E�X���������u�ԂƗ������u��

	XMFLOAT2 UVPosition_;				//�p�Y����ʏ�̈ʒu

	void InitialPosition(char pos);		//�����ʒu�𐶐�����
	float MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);	//�s��������ă}�E�X�J�[�\���̃��C�����
public:
	friend Screen_Puzzle;

	Goal(GameObject* parent);
	~Goal();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	XMFLOAT2 GetUVPos() { return UVPosition_; }
	void SetUVPos(XMFLOAT2 move);
};