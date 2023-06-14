#pragma once

enum class Difficulty
{
	EASY = 0,
	HARD
};

namespace Storage
{
	void SetDifficulty(Difficulty dif);
	const Difficulty GetDifficulty();

	void SetFadeoutMode(int mode);
	int GetFadeoutSpeed();
};