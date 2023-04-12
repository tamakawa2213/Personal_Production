#include "ModeScene.h"
#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/RootUI.h"

ModeScene::ModeScene(GameObject* parent)
	: GameObject(parent, "ModeScene")
{
}

ModeScene::~ModeScene()
{
}

void ModeScene::Initialize()
{
	Direct3D::SplitScrMode = SCREEN_FULL;

	SET_UI(ModeScene_UI);
}

void ModeScene::Update()
{
}

void ModeScene::Release()
{
}

void ModeScene::Draw()
{
}