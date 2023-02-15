#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/IniOperator.h"
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

	int e = IniOperator::AddList("Assets\\ImageStatus.ini", "Button_Easy.png");
	int h = IniOperator::AddList("Assets\\ImageStatus.ini", "Button_Hard.png");

	/*transform_.position_ = Math::PixelToTransform({
		(float)IniOperator::GetValue(e, "x", 0),
		(float)IniOperator::GetValue(e, "y", 0), 0 });
	Image::SetTransform(hPict_.at((int)Difficulty::EASY), transform_);
	transform_.position_ = Math::PixelToTransform({
		(float)IniOperator::GetValue(h, "x", 0),
		(float)IniOperator::GetValue(h, "y", 0), 0 });
	Image::SetTransform(hPict_.at((int)Difficulty::HARD), transform_);*/
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
