#include "ClearScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "Engine/SceneManager.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), hPict_(-1)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	Direct3D::SplitScrMode = SCREEN_FULL;
	ILoad(hPict_, "Assets\\Clear.png");
}

void ClearScene::Update()
{
	if (Input::IsKeyAdd())
	{
		SCENE_CHANGE(SCENE_ID_MODE);
	}
}

void ClearScene::Draw()
{
	Image::Draw(hPict_);
}

void ClearScene::Release()
{
}
