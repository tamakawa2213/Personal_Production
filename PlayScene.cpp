#include "PlayScene.h"
#include "Player.h"
#include "Storage.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Storage::SetDifficulty(HARD);
	Instantiate<Player>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Release()
{
}
