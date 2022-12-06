#include "Math.h"

namespace Math
{
    float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
    {
        return a.x * b.y * c.z +
            a.z * b.x * c.y +
            a.y * b.z * c.x -
            a.z * b.y * c.x -
            a.y * b.x * c.z -
            a.x * b.z * c.y;
    }

    bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
    {
        XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
        XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
        XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
        dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

        float u, v, l;
        u = Det(d, b, dir) / Det(a, b, dir);
        v = Det(a, d, dir) / Det(a, b, dir);
        l = Det(a, b, d) / Det(a, b, dir);
        if (u + v <=  1 && l >= 0 && u >= 0 && v >= 0)
        {
            return true;
        }
        return false;
    }

    bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist)
    {
        XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
        XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
        XMFLOAT3 d = XMFLOAT3(start.x - v0.x, start.y - v0.y, start.z - v0.z);
        dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

        float u, v, l;
        u = Det(d, b, dir) / Det(a, b, dir);
        v = Det(a, d, dir) / Det(a, b, dir);
        l = Det(a, b, d) / Det(a, b, dir);
        if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0)
        {
            if (*dist > l)
            {
                *dist = l;
                return true;
            }
            
        }
        return false;
    }

    bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
    {
        XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
        XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
        XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

        XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
        float dist;
        dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

        XMVECTOR vDir = XMLoadFloat3(&dir);
        vDir = XMVector3Normalize(vDir);
        XMStoreFloat3(&dir, vDir);

        dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

        float u, v, l;
        u = Det(d, b, dir) / Det(a, b, dir);
        v = Det(a, d, dir) / Det(a, b, dir);
        l = Det(a, b, d) / Det(a, b, dir);
        if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l < dist)
        {
            return true;
        }
        return false;
    }

    int GetDigits(int value, int m, int n)
    {
        int val = n + 1;
        int result;

        //n���ڈȉ��̌����擾
        val = value % (int)pow(10, val);

        //m���ڈȏ�̌����擾
        result = val / pow(10, m);

        return result;
    }

    std::vector<int> MakePrime(int article)
    {
        std::vector<int> ans;   //�ŏI�I�ɓ����ƂȂ�z��
        ans.clear();            //������
        ans.reserve(article);   //�z��̗v�f�����m��

        std::vector<int> sieve; //�G���g�X�e�l�X���
        sieve.clear();          //������
        sieve.push_back(2);     //2���猟���J�n����

        ans.push_back(2);       //�Ăяo����1�ȏ�̒l��O��Ƃ���̂ŗ\��2������
        
        int PrimeNumber = 3;    //�����Ώۂ̐��l : �����l��3�ɂ���

        bool IsPrime = true;   //�����Ώۂ��f�����ǂ����𔻒肳����

        //�z��̗v�f�����w�肵�����𒴂���܂ő}��
        while ((int)ans.size() < article)
        {
            //ans��sieve���v�f���������ꍇ�ɌĂяo��
            if (ans.size() > sieve.size())
            {
                //sieve�̍Ō���̒l = ans��sieve.size()�Ɋi�[����Ă���l�Ȃ̂�
                //���̎��̒l�̓�悪�����Ώۂ�菬�������
                if (PrimeNumber >= pow((double)ans.at(sieve.size()), 2))
                {
                    sieve.push_back(ans.at(sieve.size()));  //sieve�ɂ��̒l���i�[
                }
            }

            //sieve�̗v�f���ɔ��肳����
            for (int i = 0; i < sieve.size(); i++)
            {
                //sieve�̗v�f�̒l�Ŋ���؂ꂽ��
                if (PrimeNumber % sieve.at(i) == 0)
                {
                    IsPrime = false;    //IsPrime��|����
                    break;              //�����I��
                }
            }

            if (IsPrime)   //�����Ώۂ��f���Ȃ��
            {
                ans.push_back(PrimeNumber); //�v�f�ɒǉ�
            }

            IsPrime = true; //IsPrime�������I�ɗ�������

            //�����̑f����2�ȊO�ɑ��݂��Ȃ��̂�
            PrimeNumber += 2;   //PrimeNumber��2�����Z������
        }
        return ans;
    }
}