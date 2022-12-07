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
	long SEED = ran();		//�V�[�h�l
	int DesidedValue;		//�ŏI�I�ɐ��������l
	std::vector<int> Prime;	//�f���Q�ł���������

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
		Prime.clear();
		Prime.reserve(10);
		Prime = Math::MakePrime(10);
		for(int i = 0; i < 10; i++)
		{
			SEED += Prime.at(i);
			SEED *= Prime.at(i);
			if (SEED >= INT_MAX)	//int�̍ő�l�𒴂����ꍇ
			{
				SEED -= UINT_MAX;	//uint�̍ő�l������
			}
			if (SEED <= INT_MIN)	//int�̍ŏ��l����������ꍇ
			{
				SEED += UINT_MAX;	//uint�̍ő�l�𑫂�
			}
			SEED -= Prime.at(i);
		}
		SEED -= Math::GetDigits(SEED, 1, 1);	//���̂܂ܗ����Ƌ��������������Ȃ��̂�2���ڂ̒l�ň���
		DesidedValue = (int)SEED;
		return DesidedValue;
	}
}