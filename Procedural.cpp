#include "Procedural.h"
#include "Engine/Math.h"
#include <climits>
#include <stdlib.h>
#include <random>

namespace Procedural
{
	std::random_device ran;
	//変数
	int SEED = ran();		//シード値
	int DesidedValue;		//最終的に生成される値

	void SetSeed(int seed)
	{
		SEED = seed;
	}

	int FormValue()
	{
		//やりたいようにやってみる
		{
			SEED *= 3;
			SEED += 50085;
			if (SEED & 1)
			{
				SEED *= 100003;
			}
			SEED = ~SEED;
			SEED -= 97;
			SEED *= 199;
			if (Math::GetDigits(SEED, 1, 1) != 0)
			{
				SEED *= Math::GetDigits(SEED, 1, 1);
				SEED = ~SEED;
			}
			SEED *= 503;
		}

		DesidedValue = SEED;
		return DesidedValue;
	}
}