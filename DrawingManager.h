#pragma once

class RootJob;

//描画の管理をする名前空間
namespace DrawingManager
{
	void ChangeDraw();
	void Draw(RootJob* pRootJob);
}