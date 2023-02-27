#pragma once
#include "IDObject.h"

class Screen_Puzzle;
class Screen_Room;

class Player : public IDObject
{
	Screen_Puzzle* pSP;
	Screen_Room* pSR;

	XMFLOAT2 UVPosition_;	//�p�Y����ʏ�̈ʒu

	bool Wait_;				//�ҋ@��Ԃ��ǂ���
	bool MoveRoom_;

	char DoorPath_;

	bool SameGoal_;			//�S�[���Ɠ��ʒu���ǂ���
public:
	Player(GameObject* parent);

	~Player();

	void Initialize() override;

	void Update() override;

	void Release() override;

	void ReceiveFromDoor();

	XMFLOAT2 GetUVPos() { return UVPosition_; }
	void SetUVPos(XMFLOAT2 move);

	bool GetWait() { return Wait_; }
	void SetWait(bool wait);

	void SetGoal(bool Goal) { SameGoal_ = Goal; }
	bool GetGoal() { return SameGoal_; }
};