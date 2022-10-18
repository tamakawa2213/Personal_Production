#pragma once
#include "Engine/GameObject.h"

#define BoardSize_  4			//横・縦それぞれの大きさ
#define Empty_ -1				//空白のマス

struct Door	//通れるドアをビットで示す(上、下、右、左の順)
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
	{0,1},		//右
	{0,-1},		//左
	{1,0},		//上
	{-1,0}		//下
};

enum
{
	Board_HLt,
	Board_HR,
	Board_LwLt,
	Board_LwR,
	Board_LtR,
	Board_MAX		//ボードの種類の最大値
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

