#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Storage.h"
#include "../IntegratedEngine/Engine/Input.h"

ModeScene_UI::ModeScene_UI(GameObject* parent)
	: GameObject(parent, "ModeScene_UI")
{
	hPict_.clear();
}

ModeScene_UI::~ModeScene_UI()
{
}

void ModeScene_UI::Initialize()
{
	int pict = Image::Load("Assets\\Button_Easy.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	pict = Image::Load("Assets\\Button_Hard.png");
	assert(pict >= 0);

	hPict_.push_back(pict);

	transform_.position_.y = 0.25f;
	Image::SetTransform(hPict_.at((int)Difficulty::EASY), transform_);
	transform_.position_.y = -0.5f;
	Image::SetTransform(hPict_.at((int)Difficulty::HARD), transform_);
}

void ModeScene_UI::Update()
{
	if (Input::IsMouseDown(0))
	{
		if (Image::IsHitCursor(hPict_.at((int)Difficulty::EASY)))
		{
			Storage::SetDifficulty(Difficulty::EASY);
			SCENE_CHANGE(SCENE_ID_PLAY);
		}
		if (Image::IsHitCursor(hPict_.at((int)Difficulty::HARD)))
		{
			Storage::SetDifficulty(Difficulty::HARD);
			SCENE_CHANGE(SCENE_ID_PLAY);
		}
	}
}

void ModeScene_UI::Draw()
{
	for (int i = 0; i < hPict_.size(); i++)
	{
		Image::Draw(hPict_.at(i));
	}
}

void ModeScene_UI::Release()
{
}
