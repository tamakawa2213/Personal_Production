#include "Math.h"
#include <math.h>

float Math::Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c)
{
    return a.x * b.y * c.z +
        a.z * b.x * c.y +
        a.y * b.z * c.x -
        a.z * b.y * c.x -
        a.y * b.x * c.z -
        a.x * b.z * c.y;
}

//OŠpŒ`‚Ì“–‚½‚è”»’è
bool Math::Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    //1•Ó‚Ì’·‚³‚ğ‹‚ß‚é
    XMFLOAT3 e01 = XMFLOAT3{ v1.x - v0.x,v1.y - v0.y, v1.z - v0.z };
    XMFLOAT3 e02 = XMFLOAT3{ v2.x - v0.x,v2.y - v0.y, v2.z - v0.z };
    start.x = start.x - v0.x;
    start.y = start.y - v0.y;
    start.z = start.z - v0.z;
    //u,v,l‚Ì“š‚¦‚ğ‹‚ß‚é
    XMFLOAT3 result = XMFLOAT3{ Det(start,e02,dir) / Det(e01,e02,dir),Det(e01,start,dir) / Det(e01,e02,dir),-Det(e01,e02,start) / Det(e01,e02,dir) };

    //u‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
    if (0 <= result.x && result.x <= 1)
    {
        //v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
        if (0 <= result.y && result.y <= 1)
        {
            //u+v‚Ì“š‚¦‚ª0‚æ‚è‘å‚«‚­1‚æ‚è¬‚³‚¢‚©
            if (result.x + result.y <= 1)
            {
                //l‚Í0‚æ‚è‘å‚«‚¢‚©
                if (0 <= result.z)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Math::SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

    XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
    float Dist;
    Dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

    XMVECTOR vDir = XMLoadFloat3(&dir);
    vDir = XMVector3Normalize(vDir);
    XMStoreFloat3(&dir, vDir);

    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u, v, l;
    u = Det(d, b, dir) / Det(a, b, dir);
    v = Det(a, d, dir) / Det(a, b, dir);
    l = Det(a, b, d) / Det(a, b, dir);
    if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l <= Dist)
    {
        return true;
    }
    return false;
}

bool Math::SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMFLOAT3 d = XMFLOAT3(segstart.x - v0.x, segstart.y - v0.y, segstart.z - v0.z);

    XMFLOAT3 dir = XMFLOAT3(segend.x - segstart.x, segend.y - segstart.y, segend.z - segstart.z);
    float Dist;
    Dist = (float)sqrt(pow(dir.x, 2.0) + pow(dir.y, 2.0) + pow(dir.z, 2.0));

    XMVECTOR vDir = XMLoadFloat3(&dir);
    vDir = XMVector3Normalize(vDir);
    XMStoreFloat3(&dir, vDir);

    dir = XMFLOAT3(-dir.x, -dir.y, -dir.z);

    float u, v, l;
    u = Det(d, b, dir) / Det(a, b, dir);
    v = Det(a, d, dir) / Det(a, b, dir);
    l = Det(a, b, d) / Det(a, b, dir);

    if (*dist > l && l > 0.0f)
    {
        *dist = l;
    }

    if (u + v <= 1 && l >= 0 && u >= 0 && v >= 0 && l <= Dist)
    {
        return true;
    }
    return false;
}

bool Math::CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMVECTOR vA = XMLoadFloat3(&a), vB = XMLoadFloat3(&b);
    XMVECTOR outer = XMVector3Cross(vA, vB);
    outer = XMVector3Normalize(outer);
    outer = outer * size;
    XMVECTOR vCenter = XMLoadFloat3(&center);
    outer += vCenter;
    XMFLOAT3 fouter;
    XMStoreFloat3(&fouter, outer);
    bool hit = SegmentToPlane(center, fouter, v0, v1, v2);
    return hit;
}

bool Math::CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist)
{
    XMFLOAT3 a = XMFLOAT3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    XMFLOAT3 b = XMFLOAT3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    XMVECTOR vA = XMLoadFloat3(&a), vB = XMLoadFloat3(&b);
    XMVECTOR outer = XMVector3Cross(vA, vB);
    outer = XMVector3Normalize(outer);
    outer = outer * size;
    XMVECTOR vCenter = XMLoadFloat3(&center);
    outer += vCenter;
    XMFLOAT3 fouter;
    XMStoreFloat3(&fouter, outer);
    bool hit = SegmentToPlane(center, fouter, v0, v1, v2, dist);
    return hit;
}