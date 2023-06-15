#include "PlayScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/RootUI.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "../IntegratedEngine/Graphics/imgui.h"
#include "Judge.h"
#include "Player.h"
#include "PlayScene_UI.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Direct3D::SplitScrMode = SCREEN_MODE::SPLIT_2;
	Instantiate<Player>(this);
	Judge::Initialize();
	SET_UI(PlayScene_UI);
}

void PlayScene::Update()
{
	Judge::JudgeClear();
}

void PlayScene::ShowGraphical()
{
	ImGui::Begin("Test");
	ImGui::Text("Time = %g", Time::GetSeconds<float>());
	ImGui::Text("NoM = %d", Judge::GetNom());
	ImGui::Text("Score = %d", Judge::GetScore());
	ImGui::End();
}

void PlayScene::Release()
{
}
