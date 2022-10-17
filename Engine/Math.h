#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	//三角形の当たり判定
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//線分と平面の当たり判定
	//第一引数 : 線分の始点 第二引数 : 線分の終点 第三～第五引数 : ポリゴンの各頂点
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);

	//球と平面の当たり判定
	//第一引数 : 球の中心位置 第二引数 : 球の半径 第三～第五引数 : ポリゴンの各頂点
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);
};
