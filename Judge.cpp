#include "Judge.h"
#include <algorithm>
#include <list>
#include "../IntegratedEngine/Engine/Time.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"
#include "Goal.h"
#include "SceneList.h"
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
        default:break;
        }

        float NpS;          //1�b������̎萔
        NpS = NoM / Time::GetSeconds<float>();

        Score = (int)(std::max((1 - (NoM / 50.0f)), 0.0f) + (10 / Time::GetSeconds<float>()) * (NpS + 1) * revision * 1000);
    }
    
    int GetScore()
    {
        return Score;
    }

    void JudgeClear()
    {
       /* if(!GoalList_.empty())
        for (auto itr = GoalList_.begin(); itr != GoalList_.end();)
        {
            if (!(*itr).use_count())
            {
                itr = GoalList_.erase(itr);
            }
            else
            {
                itr++;
            }
        }*/

        //if (GoalList_.empty())
        if(PtrObserver::GetSceneManager()->FindObject("Goal") == nullptr)
        {
            calculation();
            SCENE_CHANGE(SCENE_ID::CLEAR);
        }
    }
}