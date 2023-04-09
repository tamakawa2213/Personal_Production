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
	//‰æ–Ê•ªŠ„‚ğ‹­§I—¹
	Direct3D::SplitScrMode = SCREEN_FULL;

	SET_UI(ClearScene_UI);
	//Instantiate<ClearScene_UI>(this);
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
