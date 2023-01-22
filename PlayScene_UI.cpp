#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Picture.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "PlayScene_Menu.h"

PlayScene_UI::PlayScene_UI(GameObject* parent)
	: GameObject(parent, "PlayScene_UI")
{
	hPict_.clear();
}

PlayScene_UI::~PlayScene_UI()
{
}

void PlayScene_UI::Initialize()
{
	int pict = Picture::Load("Assets\\Button_Menu.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	transform_.position_ = { -0.7f, 0.8f, 0 };
	Picture::SetTransform(hPict_.at(0), transform_);
}

void PlayScene_UI::Update()
{
	if (Input::IsMouseDown(0) && Picture::IsHitCursor(hPict_.at(0)))
	{
		Instantiate<PlayScene_Menu>(GetParent());
	}
}

void PlayScene_UI::DrawUnique()
{
	Picture::Draw(hPict_.at(0));
}

void PlayScene_UI::Release()
{
}
