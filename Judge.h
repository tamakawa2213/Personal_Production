#pragma once

class Goal;

namespace Judge
{
	void Initialize();	//初期化
	void AddNom();		//手数の加算
	int GetNom();
	void calculation();	//スコアの算出
	int GetScore();		//スコアを取得する

	//クリアしたか判定
	void JudgeClear();

	void AddGoal(Goal* g);
};