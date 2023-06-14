#pragma once

class Goal;

enum class Difficulty
{
	EASY = 0,
	HARD
};

namespace Storage
{
	void SetDifficulty(Difficulty dif);
	Difficulty GetDifficulty();

	void SetFadeoutMode(int mode);
	int GetFadeoutSpeed();

	void InsertGoal(Goal* g);
};