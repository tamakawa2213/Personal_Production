#include "ClearScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	Direct3D::SplitScrMode = SCREEN_FULL;

}

void ClearScene::Update()
{
}

void ClearScene::Release()
{
}
