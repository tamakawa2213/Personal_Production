#pragma once

#include <dInput.h>
#include < DirectXMath.h >
#include "XInput.h"
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib,"Xinput.lib")

using namespace DirectX;


#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	HRESULT Initialize(HWND hWnd);
	void Update();
	//キーの処理
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	bool IsKeyUpDown(int keyCode);
	//マウス処理
	bool IsMouce(int mouceCode);
	bool IsMouceDown(int mouceCode);
	bool IsMouceUp(int mouceCode);
	bool IsMouceUpDown(int mouceCode);
	XMFLOAT3 GetMousePosition();
	void SetMousePosition(int x, int y);
	//コントローラー処理
	bool IsController(int controllerCode, int controllerID = 0);
	bool IsControllerDown(int controllerCode, int controllerID = 0);
	bool IsControllerUp(int controllerCode, int controllerID = 0);
	bool IsControllerUpDown(int controllerCode, int controllerID = 0);
	XMFLOAT3 GetPadStickL(int controllerID = 0);
	XMFLOAT3 GetPadStickR(int controllerID = 0);

	void Release();
};