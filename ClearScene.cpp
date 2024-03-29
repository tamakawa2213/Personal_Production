#include "ClearScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/RootUI.h"
#include "ClearScene_UI.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene")
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	//画面分割を強制終了
	Direct3D::SplitScrMode = SCREEN_MODE::FULL;

	SET_UI(ClearScene_UI);
}

void ClearScene::Update()
{
}

void ClearScene::Draw()
{
}

void ClearScene::Release()
{
}
