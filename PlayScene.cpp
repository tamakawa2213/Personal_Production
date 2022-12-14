#include "PlayScene.h"
#include "Engine/Time.h"
#include "Graphics/imgui.h"
#include "Judge.h"
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
	Storage::SetDifficulty(Difficulty::EASY);
	Instantiate<Player>(this);
	Judge::Initialize();
}

void PlayScene::Update()
{
	ImGui::Begin("Test");
	ImGui::Text("Time = %g", Time::GetTimef());
	ImGui::Text("NoM = %d", Judge::GetNom());
	ImGui::Text("Score = %d", Judge::GetScore());
	ImGui::End();
}

void PlayScene::Release()
{
}
