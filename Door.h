#pragma once
#include "IDObject.h"

class Door : public IDObject
{
	int hModel_;
	bool RayHit_;						//���C���������Ă��邩�ǂ���

	bool IsMouse_[2];					//�}�E�X���������u�ԂƗ������u��

	void SendtoPlayer();				//Player�N���X��ID�𑗂�
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};