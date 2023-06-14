#include "Storage.h"
#include <map>
#include "Goal.h"

namespace
{
	std::map<int, int> Fadeout = {
		{0,150},
		{1,100},
		{2,50}
	};

	int FoMode = 0;	//フェードアウトのモード

	std::list<Goal*> GoalList_;
}

namespace Storage
{
	Difficulty Dif;


	void SetDifficulty(Difficulty dif)
	{
		Dif = dif;
	}
	Difficulty GetDifficulty()
	{
		return Dif;
	}

	void SetFadeoutMode(int mode)
	{
		FoMode = mode;
	}

	int GetFadeoutSpeed()
	{
		return Fadeout[FoMode];
	}

	void InsertGoal(Goal* g)
	{
		GoalList_.push_back(g);
	}
}