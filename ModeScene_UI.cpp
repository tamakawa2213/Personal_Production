#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Math.h"
#include "Engine/SceneManager.h"
#include "Storage.h"

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

	const wchar_t* filename = L"Assets\\Setting.ini";
	transform_.position_ = Math::PixelToTransform({
		(float)GetPrivateProfileInt(L"IMAGE", L"Easy_x", 0, filename),
		(float)GetPrivateProfileInt(L"IMAGE", L"Easy_y", 0, filename), 0 });
	Image::SetTransform(hPict_.at((int)Difficulty::EASY), transform_);
	transform_.position_ = Math::PixelToTransform({
		(float)GetPrivateProfileInt(L"IMAGE", L"Hard_x", 0, filename),
		(float)GetPrivateProfileInt(L"IMAGE", L"Hard_y", 0, filename), 0 });
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
