#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class Player;
class Screen_Puzzle;

class Goal : public GameObject
{
	int hModel_;
	bool RayHit_;						//���C���������Ă��邩�ǂ���

	bool IsMouse_[2];					//�}�E�X���������u�ԂƗ������u��

	XMFLOAT2 UVPosition_;				//�p�Y����ʏ�̈ʒu

	Player* pPlayer_;

	void InitialPosition(char pos);		//�����ʒu�𐶐�����
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