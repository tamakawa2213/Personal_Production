#include "Procedural.h"
#include "Engine/Math.h"
#include <climits>
#include <stdlib.h>
#include <random>

namespace Procedural
{
	std::random_device ran;
	//�ϐ�
	int SEED = ran();		//�V�[�h�l
	int DesidedValue;		//�ŏI�I�ɐ��������l

	void SetSeed(int seed)
	{
		SEED = seed;
	}

	int FormValue()
	{
		//��肽���悤�ɂ���Ă݂�
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