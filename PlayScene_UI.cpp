#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
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
	int pict = Image::Load("Assets\\Button_Menu.png");
	assert(pict >= 0);

	hPict_.push_back(pict);
}

void PlayScene_UI::Update()
{
	if (Input::IsMouseDown(0) && Image::IsHitCursor(hPict_.at(0)))
	{
		Instantiate<PlayScene_Menu>(GetParent());
	}
}

void PlayScene_UI::DrawUnique()
{
	Image::Draw(hPict_.at(0));
}

void PlayScene_UI::Release()
{
}
