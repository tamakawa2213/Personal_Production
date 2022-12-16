#include "Procedural.h"
#include "Engine/Math.h"
#include <climits>
#include <stdlib.h>
#include <random>
#include <vector>

namespace Procedural
{
	std::random_device ran;
	//�ϐ�
	int SEED = ran();		//�V�[�h�l

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