#include "Procedural.h"
#include "Engine/Math.h"
#include <climits>
#include <stdlib.h>
#include <random>
#include <vector>

namespace Procedural
{
	std::random_device ran;
	//変数
	int SEED = ran();		//シード値

	void SetSeed()
	{
		SEED = ran();
	}

	void SetSeed(int seed)
	{
		SEED = seed;
	}

	int FormValue()
	{
		return Math::xorshift32(SEED);
	}
}