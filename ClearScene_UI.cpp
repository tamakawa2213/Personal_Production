#include "ClearScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "Engine/SceneManager.h"

ClearScene_UI::ClearScene_UI(GameObject* parent)
	: MouseOperationUI(parent, "ClearScene_UI"), hPict_(-1)
{
}

ClearScene_UI::~ClearScene_UI()
{
}

void ClearScene_UI::Initialize()
{
	ILoad(hPict_, "Assets\\ToTitle.png");
}

void ClearScene_UI::ClickLeftFirst()
{
	if (Image::IsHitCursor(hPict_))
	{
		SCENE_CHANGE(SCENE_ID::MODE);
	}
}

void ClearScene_UI::DrawUnique()
{
	Image::Draw(hPict_);
}

void ClearScene_UI::Release()
{
}
