#include "Door.h"
#include "Engine/Model.h"

Door::Door(GameObject* parent)
	: GameObject(parent, "Door"), hModel_(-1)
{
}

Door::~Door()
{
}

void Door::Initialize()
{
	hModel_ = Model::Load("Assets\\Door.fbx");
	assert(hModel_ >= NULL);
}

void Door::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}
