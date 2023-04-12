#include "PlayScene_UI.h"
#include "../IntegratedEngine/Engine/CallDef.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"
#include "PlayScene_Menu.h"

PlayScene_UI::PlayScene_UI()
	: UserInterface(), hPict_(-1)
{
}

PlayScene_UI::~PlayScene_UI()
{
}

void PlayScene_UI::Initialize()
{
	hPict_ = Image::Load("Assets\\Button_Menu.png");
	assert(hPict_ >= 0);
}

void PlayScene_UI::Update()
{
	if (Input::Mouse::Down(0) && Image::IsHitCursor(hPict_))
	{
		//ƒƒjƒ…[‚ðŠJ‚­
		PtrObserver::GetRootUI()->Link<PlayScene_Menu>();
	}
}

void PlayScene_UI::Draw()
{
	Image::Draw(hPict_);
}

void PlayScene_UI::Release()
{
}
