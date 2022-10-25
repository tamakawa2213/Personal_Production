#pragma once
#include "Engine/GameObject.h"


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
	Room_HLt,
	Room_HR,
	Room_LwLt,
	Room_LwR,
	Room_LtR,
	Room_MAX		//�����̎�ނ̍ő�l
};

class Screen_Room : public GameObject
{
	int hModel_[Room_MAX];
public:
	Screen_Room(GameObject* parent);

	~Screen_Room();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};
