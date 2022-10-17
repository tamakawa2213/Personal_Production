#include "Image.h"
#include "CallDef.h"

namespace Image
{
	std::vector<Image*> ImageList_;
}

int Image::Load(LPCWSTR fileName)
{
	Image* pLoadImage;
	pLoadImage = new Image;
	pLoadImage->FileImage = fileName;

	for (auto itr = ImageList_.begin(); itr < ImageList_.end(); itr++)
	{
		if (fileName == (*itr)->FileImage)
		{
			pLoadImage->pSprite = (*itr)->pSprite;
			break;
		}
	}
	pLoadImage->pSprite = new Sprite;
	pLoadImage->pSprite->Initialize(pLoadImage->FileImage);
	ImageList_.push_back(pLoadImage);
	return (int)ImageList_.size() - 1;
}

void Image::Draw(int hPict)
{
	ImageList_[hPict]->color_ = { ImageList_[hPict]->red_, ImageList_[hPict]->green_, ImageList_[hPict]->blue_, ImageList_[hPict]->alpha_ };
	ImageList_[hPict]->pSprite->Draw(ImageList_[hPict]->TransformImage, ImageList_[hPict]->color_);
}


void Image::Release()
{
	for (int i = 0; i < ImageList_.size(); i++)
	{
		bool isExist = false;	//今消そうとしているSpriteデータを参照してるやつがいるかどうか
		for (int j = i + 1; j < ImageList_.size(); j++)
		{
			if (ImageList_[i]->pSprite == ImageList_[j]->pSprite)
			{
				isExist = true;
				break;
			}
		}
		//もうそのデータを誰も参照してなければ
		if (!isExist)
		{
			SAFE_DELETE(ImageList_[i]->pSprite);
		}
		SAFE_DELETE(ImageList_[i]);
	}
	ImageList_.clear();
}

void Image::AllRelease()
{
	for (int i = 0; i < ImageList_.size(); i++)
	{
		if (ImageList_[i] != nullptr)
		{
			Release();
		}
	}
	ImageList_.clear();
}

//透明度の取得
void Image::SetAlpha(int hPict, int alpha)
{
	ImageList_[hPict]->alpha_ = (float)alpha / UINT8_MAX;
}

//RGBの色の取得	
void Image::SetColor(int hPict, int red, int blue, int green)
{
	ImageList_[hPict]->red_ = (float)red / UINT8_MAX;
	ImageList_[hPict]->green_ = (float)green / UINT8_MAX;
	ImageList_[hPict]->blue_ = (float)blue / UINT8_MAX;
}

//移動・回転・拡大縮小の取得
void Image::SetTransform(int hPict, Transform transform_)
{
	ImageList_[hPict]->TransformImage = transform_;
}

//レイキャスト（レイを飛ばして当たり判定）
void Image::RayCast(int hPict, RayCastData* data)
{
	XMFLOAT3 target;
	target.x = data->start.x + data->dir.x;
	target.y = data->start.y + data->dir.y;
	target.z = data->start.z + data->dir.z;
	XMMATRIX matInv = XMMatrixInverse(nullptr, ImageList_[hPict]->TransformImage.GetWorldMatrix());
	XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
	XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
	XMVECTOR vecDir = vecTarget - vecStart;

	XMStoreFloat3(&data->start, vecStart);
	XMStoreFloat3(&data->dir, vecDir);

	ImageList_[hPict]->pSprite->RayCast(data);
}