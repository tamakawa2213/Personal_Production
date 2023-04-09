#include "ClearScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Text.h"
#include "Engine/SceneManager.h"
#include "Judge.h"

ClearScene_UI::ClearScene_UI(RootUI* ui)
	: UserInterface(ui), hPict_(-1), pText_(nullptr)
{
}

ClearScene_UI::~ClearScene_UI()
{
}

void ClearScene_UI::Initialize()
{
	ILoad(hPict_, "Assets\\ToTitle.png");

	std::unique_ptr<FontData> data = std::make_unique<FontData>();
	data->fontSize = 10;
	pText_ = std::make_unique<Text>(data.get());
	pText_->Initialize();
}

void ClearScene_UI::Update()
{
	if (Input::Mouse::Down(0) && Image::IsHitCursor(hPict_))
	{
		pRootUI_->SceneChange(SCENE_ID::MODE);
	}
}

void ClearScene_UI::Draw()
{
	Image::Draw(hPict_);
	pText_->Draw({ 15,45 }, "Score : %d", Judge::GetScore());
}

void ClearScene_UI::Release()
{
	pText_->Release();
}
