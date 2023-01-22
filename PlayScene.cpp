#include "PlayScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "../IntegratedEngine/Graphics/imgui.h"
#include "Judge.h"
#include "Player.h"
#include "PlayScene_UI.h"
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
	Direct3D::SplitScrMode = SCREEN_SPLIT_2;
	Instantiate<Player>(this);
	Judge::Initialize();
	Instantiate<PlayScene_UI>(this);
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
