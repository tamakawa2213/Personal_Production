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
	void Draw(int hModel, char SHADER_TYPE = 1);
	void Draw(int hModel, XMFLOAT3 Chroma, float Bright, float Alpha, char SHADER_TYPE = 1);

	void Release();

	void RayCast(int hModel, RayCastData& Raydata);
}