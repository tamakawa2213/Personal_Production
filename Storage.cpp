#include "Storage.h"
#include <map>

namespace
{
	std::map<int, int> Fadeout = {
		{0,150},
		{1,100},
		{2,50}
	};

	int FoMode = 0;	//フェードアウトのモード

	Difficulty Dif;
}

namespace Storage
{
	void SetDifficulty(Difficulty dif)
	{
		Dif = dif;
	}
	const Difficulty GetDifficulty()
	{
		return Dif;
	}

	void SetFadeoutMode(int mode)
	{
		FoMode = mode;
	}

	int GetFadeoutMode()
	{
		return FoMode;
	}

	int GetFadeoutSpeed()
	{
		return Fadeout[FoMode];
	}
}