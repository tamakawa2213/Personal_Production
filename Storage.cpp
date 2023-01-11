#include "Storage.h"

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
}