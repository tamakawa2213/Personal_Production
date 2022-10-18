#include "PlayScene.h"
#include "Screen_Puzzle.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Instantiate<Screen_Puzzle>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Release()
{
}
