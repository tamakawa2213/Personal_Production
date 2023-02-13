#include "ModeScene.h"
#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Debug.h"
#include "../IntegratedEngine/Engine/Image.h"

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
	Instantiate<ModeScene_UI>(this);
	//hPict = Image::Load("Assets\\FreeSizeSample.png");
}

void ModeScene::Update()
{
}

void ModeScene::Release()
{
}

void ModeScene::Draw()
{
	//Image::Draw(hPict);
}

void ModeScene::DebugMode()
{
	Debug::ImagePositioning();
}
