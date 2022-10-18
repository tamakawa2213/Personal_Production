#pragma once
#include <string>
#include <vector>
#include "Sprite.h"
#include "Transform.h"

struct PictureSet
{
	Sprite* pSprite = nullptr;	//Sprite�̃|�C���^
	Transform transform;		//transform�N���X
	LPCWSTR FileName = L"";		//�t�@�C���̖��O
	bool FindFbx = false;		//Fbx�t�@�C�������O�Ƀ��[�h���Ă��邩
};

namespace Picture
{
	int Load(LPCWSTR filename);
	void SetTransform(int hModel, Transform transform);
	void Draw(int hModel);

	void Release();
}