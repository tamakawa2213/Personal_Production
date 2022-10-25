#pragma once
#include "Engine/GameObject.h"


struct Move
{
	int moveHLw;
	int moveLtR;
};

const Move Direction[4]
{
	{0,1},		//右
	{0,-1},		//左
	{1,0},		//上
	{-1,0}		//下
};

enum
{
	Room_HLt,
	Room_HR,
	Room_LwLt,
	Room_LwR,
	Room_LtR,
	Room_MAX		//部屋の種類の最大値
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
