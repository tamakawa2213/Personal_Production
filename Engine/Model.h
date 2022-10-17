#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

struct Fileset
{
	Fbx* pFbx = nullptr;		//Fbxのポインタ
	Transform transform;		//transformクラス
	std::string FileName;		//ファイルの名前
	bool FindFbx = false;		//Fbxファイルを事前にロードしているか
};

namespace Model
{
	int Load(std::string filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	void Release();

	void RayCast(int hModel, RayCastData& Raydata);

	void PushOut(int handle, XMFLOAT3* position, float size, XMFLOAT3 dir);
}