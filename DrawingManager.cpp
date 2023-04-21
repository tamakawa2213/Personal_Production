#include "DrawingManager.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/PtrObserver.h"
#include "../IntegratedEngine/Engine/RootJob.h"

#include <map>

namespace DrawingManager
{
	void DrawFull(RootJob* pRootJob);
	void DrawSplit(RootJob* pRootJob);
	void DrawLeft(RootJob* pRootJob);
	void DrawRight(RootJob* pRootJob);
}

namespace
{
	std::map<SCREEN_MODE, void(*)(RootJob*)> DrawingMode_ =
	{
		{SCREEN_MODE::FULL, &DrawingManager::DrawFull},
		{SCREEN_MODE::SPLIT_2, &DrawingManager::DrawSplit}
	};

	XMVECTOR campos[2] = { {-10.0f, 5.5f, 1.2f, 0}, {1.6f, 6, 1.5f, 0} };
	XMVECTOR camtar[2] = { {-10, 0, 1.3f, 0}, {1.5f, 0, 1.5f, 0} };

	int DrawRange = VP_LEFT;
}

namespace DrawingManager
{
	void Draw(RootJob* pRootJob)
	{
		DrawingMode_[Direct3D::SplitScrMode](pRootJob);

		Direct3D::SetViewPort(VP_FULL);

		pRootJob->DrawUniqueSub();
	}

	void DrawSplit(RootJob* pRootJob)
	{
		//マウスの位置によって描画順を変更
		if (Input::Mouse::GetPosition().x < Direct3D::scrWidth / 2)
		{
			DrawRight(pRootJob);
			DrawLeft(pRootJob);
		}
		else
		{
			DrawLeft(pRootJob);
			DrawRight(pRootJob);
		}
	}

	void DrawFull(RootJob* pRootJob)
	{
		Direct3D::SetViewPort(VP_FULL);
		switch (DrawRange)
		{
		case VP_LEFT:
			Camera::SetPosition(campos[0]);
			Camera::SetTarget(camtar[0]);
			break;
		case VP_RIGHT:
			Camera::SetPosition(campos[1]);
			Camera::SetTarget(camtar[1]);
			break;
		default: break;
		}
		Camera::Update();
		//全オブジェクトを描画
		//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
		pRootJob->DrawSub();
	}

	void DrawLeft(RootJob* pRootJob)
	{
		Direct3D::SetViewPort(VP_LEFT);
		Camera::SetPosition(campos[0]);
		Camera::SetTarget(camtar[0]);

		Camera::Update();
		//全オブジェクトを描画
		//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
		pRootJob->DrawSub();
	}

	void DrawRight(RootJob* pRootJob)
	{
		Direct3D::SetViewPort(VP_RIGHT);
		Camera::SetPosition(campos[1]);
		Camera::SetTarget(camtar[1]);

		Camera::Update();
		//全オブジェクトを描画
		//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
		pRootJob->DrawSub();
	}

	void ChangeDraw()
	{
		//spaceキーを押したら描画変更
		if (Input::Keyboard::Down(DIK_SPACE))
		{
			switch (Direct3D::SplitScrMode)
			{
			case SCREEN_MODE::FULL:
				Direct3D::SplitScrMode = SCREEN_MODE::SPLIT_2;
				break;
			case SCREEN_MODE::SPLIT_2:
				if (Input::Mouse::GetPosition().x < Direct3D::scrWidth / 2)	//マウスカーソルの位置でカメラの位置を決定
				{
					DrawRange = VP_LEFT;
				}
				else
				{
					DrawRange = VP_RIGHT;
				}
				Direct3D::SplitScrMode = SCREEN_MODE::FULL;
				break;
			default: break;
			}
		}
	}
}