#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include <vector>

static const int BoardSize_ = 4;		//横・縦それぞれの大きさ

class Player;
enum class Difficulty;

enum class Board
{
	HLt = 0,
	HR,
	LwLt,
	LwR,
	LtR,
	MAX		//ボードの種類の最大値
};

class Screen_Puzzle : public GameObject
{
	char PuzX_;
	char PuzZ_;
	int hModel_[(char)Board::MAX];	//格納されたオブジェクト番号
	int Board_[BoardSize_][BoardSize_];	//ボードのデータ
	char GoalPos_;

	int SeedData_;		//この値を基にパズルの盤面を生成
	std::vector<char> DecidedData_;		//決定済みデータ

	bool Wait_;			//待機時間かどうか

	Difficulty Mode_;			//難易度指定

	char Moving_;		//移動を開始してから経過したフレーム数を記録
	char MovingPanel_;	//移動中のマスの値が入る
	char MoveDir_;		//移動する方向

	void AssignPuzzle();					//完成系のパズル盤面を作成
	void Shuffle();							//パズルをランダムに生成する
	void AssignGoal();						//ゴールの位置を生成

	Player* pPlayer_;

	void Swap(int x, int z);				//空白に隣り合っていれば交換する
	void PrickPin();						//ピン刺し

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

