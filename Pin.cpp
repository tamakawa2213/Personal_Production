#include "Pin.h"
#include "../IntegratedEngine/Engine/Model.h"

Pin::Pin(GameObject* parent)
	: GameObject(parent, "Pin"), UVPosition_(), hModel_(-1), Disp_(false)
{
}

Pin::~Pin()
{
}

void Pin::Initialize()
{
	hModel_ = Model::Load("Assets\\Pin.fbx");
	assert(hModel_ >= 0);
	const float Scale = 0.3f;
	transform_.scale_ = Scale;
	transform_.rotate_.y = -45;
	transform_.rotate_.z = -30;
}

void Pin::Draw()
{
	if (Disp_)
	{
		transform_.position_ = Position{ UVPosition_.x, 0, UVPosition_.y };
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

void Pin::Release()
{
}
