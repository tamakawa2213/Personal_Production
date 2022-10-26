#include "PlayScene.h"
#include "Screen_Puzzle.h"
#include "Screen_Room.h"

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
	Instantiate<Screen_Room>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Release()
{
}
