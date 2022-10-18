#pragma once
#include "Fbx.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	//線分とポリゴンの当たり判定を行う関数
	//第一引数 : 線分の始点　第二引数 : 線分の終点　第三～第五引数 : ポリゴンの各頂点
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//ベクトルとポリゴンの当たり判定を行う関数
	//第一引数 : ベクトルの始点　第二引数 : ベクトルの向き　第三～第五引数 : ポリゴンの各頂点
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//距離も返す当たり判定
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist);
};