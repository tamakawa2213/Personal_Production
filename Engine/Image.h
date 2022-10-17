#pragma once
#include <string>
#include <vector>
#include "Sprite.h"
#include "Transform.h"

namespace Image
{
	struct Image
	{
		Sprite* pSprite;
		Transform TransformImage;
		LPCWSTR FileImage;
		XMFLOAT4 color_;
		float alpha_;
		float red_;
		float blue_;
		float green_;
		Image() : pSprite(nullptr),	//�R���X�g���N�^
			FileImage(L""),
			color_({ 1.0,1.0,1.0,1.0 }),
			alpha_(1.0),
			red_(1.0),
			blue_(1.0),
			green_(1.0)
		{
		}
	};
	int Load(LPCWSTR fileName);
	void Draw(int hImage_);
	void Release();
	void AllRelease();
	void SetAlpha(int hPict, int alpha);	//�����x�̎擾
	void SetColor(int hPict, int red, int blue, int green); //RBG�̎擾
	void SetTransform(int hPict, Transform transform_);
	void RayCast(int hImage, RayCastData* data);
};

