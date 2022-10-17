#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

struct Fileset
{
	Fbx* pFbx = nullptr;		//Fbx�̃|�C���^
	Transform transform;		//transform�N���X
	std::string FileName;		//�t�@�C���̖��O
	bool FindFbx = false;		//Fbx�t�@�C�������O�Ƀ��[�h���Ă��邩
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