#include "ClearScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "Engine/SceneManager.h"

ClearScene_UI::ClearScene_UI(GameObject* parent)
	: GameObject(parent, "ClearScene_UI"), hPict_(-1)
{
}

ClearScene_UI::~ClearScene_UI()
{
}

void ClearScene_UI::Initialize()
{
	ILoad(hPict_, "Assets\\ToTitle.png");
}

void ClearScene_UI::FixedUpdate()
{
	if (Input::IsMouseDown(0) && Image::IsHitCursor(hPict_))
	{
		SCENE_CHANGE(SCENE_ID_MODE);
	}
}

void ClearScene_UI::DrawUnique()
{
	Image::Draw(hPict_);
}

void ClearScene_UI::Release()
{
}
