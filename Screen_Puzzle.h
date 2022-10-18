#pragma once
#include "Engine/GameObject.h"

#define BoardSize_  4			//���E�c���ꂼ��̑傫��
#define Empty_ -1				//�󔒂̃}�X

struct Door	//�ʂ��h�A���r�b�g�Ŏ���(��A���A�E�A���̏�)
{
	const char DoorH = 0x08;
	const char DoorLw = 0x04;
	const char DoorR = 0x02;
	const char DoorLt = 0x01;
};

struct Move
{
	int moveHLw;
	int moveLtR;
};

const Move Direction[4]
{
	{0,1},		//�E
	{0,-1},		//��
	{1,0},		//��
	{-1,0}		//��
};

enum
{
	Board_HLt,
	Board_HR,
	Board_LwLt,
	Board_LwR,
	Board_LtR,
	Board_MAX		//�{�[�h�̎�ނ̍ő�l
};

class Screen_Puzzle : public GameObject
{
	int hModel_[Board_MAX];
	int Board_[BoardSize_][BoardSize_];
	void Swap(int x, int z);
public:
	Screen_Puzzle(GameObject* parent);

	~Screen_Puzzle();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

