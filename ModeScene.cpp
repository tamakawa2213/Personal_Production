#include "ModeScene.h"
#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Direct3D.h"

ModeScene::ModeScene(GameObject* parent)
	: GameObject(parent, "ModeScene")
{
}

ModeScene::~ModeScene()
{
}

void ModeScene::Initialize()
{
	//pText_ = new Text;
	//pText_->Initialize("test");
	Direct3D::SplitScrMode = SCREEN_FULL;
	Instantiate<ModeScene_UI>(this);
}

void ModeScene::Update()
{
}

void ModeScene::Release()
{
}

void ModeScene::Draw()
{
	//pText_->Draw();
}
