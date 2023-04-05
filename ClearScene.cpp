#include "ClearScene.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Text.h"
#include "ClearScene_UI.h"
#include "Judge.h"

ClearScene::ClearScene(GameObject* parent)
	: GameObject(parent, "ClearScene"), pText_(nullptr)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	std::unique_ptr<FontData> data = std::make_unique<FontData>();
	data->fontSize = 10;
	pText_ = std::make_unique<Text>(data.get());
	pText_->Initialize();

	//âÊñ ï™äÑÇã≠êßèIóπ
	Direct3D::SplitScrMode = SCREEN_FULL;

	Instantiate<ClearScene_UI>(this);
}

void ClearScene::Update()
{
}

void ClearScene::Draw()
{
	pText_->Draw({ 15,45 }, "Score : %d", Judge::GetScore());
}

void ClearScene::Release()
{
}
