#pragma once
#include "Engine/GameObject.h"

#define BoardSize_  4			//横・縦それぞれの大きさ
#define Empty_ -1				//空白のマス

struct DoorPath	//通れるドアをビットで示す(上、下、右、左の順)
{
	const char DoorH = 0x08;
	const char DoorLw = 0x04;
	const char DoorLt = 0x02;
	const char DoorR = 0x01;
};

struct Move
{
	int moveHLw;
	int moveLtR;
};

const Move Direction[4]
{
	{1,0},		//上
	{-1,0},		//下
	{0,-1},		//左
	{0,1}		//右
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
	char PuzX_;
	char PuzZ_;
	int hModel_[Board_MAX];
	int Board_[BoardSize_][BoardSize_];

	void Shuffle();

	void Swap(int x, int z);				//空白に隣り合っていれば交換する

	bool MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);		//行列をかけてマウスカーソルのレイを作る

	bool DoorConfig(char BoardType, char DoorID);
public:
	Screen_Puzzle(GameObject* parent);

	~Screen_Puzzle();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	char SendToken(XMFLOAT2 pPos, char DoorID);
};

