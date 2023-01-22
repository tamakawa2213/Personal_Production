#include "Judge.h"
#include <algorithm>
#include "../IntegratedEngine/Engine/Time.h"
#include "Storage.h"

namespace
{
    int Score;  //�X�R�A
    int NoM;	//�萔
}

namespace Judge
{
    void Initialize()
    {
        Score = 0;
        NoM = 0;
        Time::Reset();
        Time::UnLock();
    }

    void AddNom()
    {
        NoM++;
    }

    int GetNom()
    {
        return NoM;
    }

    void calculation()
    {
        Time::Lock();
        int revision = 0;   //��Փx�ɂ��X�R�A�␳
        switch (Storage::GetDifficulty())
        {
        case Difficulty::EASY: revision = 1; break;
        case Difficulty::HARD: revision = 5; break;
        }

        float NpS;          //1�b������̎萔
        NpS = NoM / Time::GetTimef();

        Score = (int)(std::max((1 - (NoM / 50.0f)), 0.0f) + (10 / Time::GetTimef()) * (NpS + 1) * revision * 1000);
    }
    
    int GetScore()
    {
        return Score;
    }
}