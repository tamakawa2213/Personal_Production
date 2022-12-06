#pragma once
#include "Engine/GameObject.h"

#define BoardSize_  4		//横・縦それぞれの大きさ
#define Empty_ -1			//空白のマス
#define TIMETOMOVE 60		//移動にかける時間
#define BOARDTOTAL_ 16		//盤面のマスの総数

class Player;

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
	int hModel_[Board_MAX];	//格納されたオブジェクト番号
	int Board_[BoardSize_][BoardSize_];	//ボードのデータ

	const char UnderSide = 8;	//ボードの下半分
	const char RightSide = 2;	//ボードの右半分
	int SeedData_;		//この値を基にパズルの盤面を生成

	bool Wait_;			//待機時間かどうか

	char Mode_;			//難易度指定

	char Moving_;		//移動を開始してから経過したフレーム数を記録
	char MovingPanel_;	//移動中のマスの値が入る
	char MoveDir_;		//移動する方向

	void AssignPuzzle();					//完成系のパズル盤面を作成
	void Shuffle();							//パズルをランダムに生成する
	void AssignGoal();						//ゴールの位置を生成

	Player* pPlayer_;

	void Swap(int x, int z);				//空白に隣り合っていれば交換する
	void PrickPin();						//ピン刺し

	bool MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);		//行列をかけてマウスカーソルのレイを作る

	bool DoorConfig(char BoardType, char DoorID);	//押したドアから隣り合う部屋に移動できるか

	void Moving();	//押してからの待機時間
public:
	Screen_Puzzle(GameObject* parent);

	~Screen_Puzzle();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	char SendToken(XMFLOAT2 pPos, char DoorID);	//Playerに移動できるかどうかを返す
};

