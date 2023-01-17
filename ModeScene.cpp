#include "ModeScene.h"
#include "ModeScene_UI.h"
#include "Engine/Direct3D.h"

ModeScene::ModeScene(GameObject* parent)
	: GameObject(parent, "ModeScene")
{
}

ModeScene::~ModeScene()
{
}

void ModeScene::Initialize()
{
	Direct3D::SplitScrMode = VP_FULL;
	Instantiate<ModeScene_UI>(this);
}

void ModeScene::Update()
{
}

void ModeScene::Release()
{
}
