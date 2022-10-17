#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;
	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevMouseState_;
	XMFLOAT3 mousePosition;

	//コントローラ
	const int MAX_NUM = 4;
	XINPUT_STATE controllerState_[MAX_NUM];
	XINPUT_STATE prevControllerState_[MAX_NUM];

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"インプットに失敗しました", L"エラー", MB_OK);
			SAFE_RELEASE(pDInput);
			return hr;
		}
		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"キーボードの取得に失敗しました", L"エラー", MB_OK);
			SAFE_RELEASE(pDInput);
			return hr;
		}
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		hr = pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"マウスの取得に失敗しました", L"エラー", MB_OK);
			SAFE_RELEASE(pDInput);
			return hr;
		}
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(keyState));
		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);

		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->Acquire();
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
		for (int i = 0; i < MAX_NUM; i++)
		{
			memcpy(&prevControllerState_[i], &controllerState_[i], sizeof(controllerState_[i]));
			XInputGetState(0, &controllerState_[i]);
		}
	}

	//キーボード
	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (prevKeyState[keyCode] != keyState[keyCode] && keyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//押されてて、今離した
		if (prevKeyState[keyCode] != keyState[keyCode] && prevKeyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUpDown(int keyCode)
	{
		//今は押してて、前回は押してない + 押されてて、今離した
		if (prevKeyState[keyCode] != keyState[keyCode])
		{
			return true;
		}
		return false;
	}

	//マウス
	bool IsMouce(int mouceCode)
	{
		if (mouseState_.rgbButtons[mouceCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouceDown(int mouceCode)
	{
		//今は押してて、前回は押してない
		if (prevMouseState_.rgbButtons[mouceCode] != mouseState_.rgbButtons[mouceCode] && mouseState_.rgbButtons[mouceCode])
		{
			return true;
		}
		return false;
	}

	bool IsMouceUp(int mouceCode)
	{
		//押されてて、今離した
		if (prevMouseState_.rgbButtons[mouceCode] != mouseState_.rgbButtons[mouceCode] && prevMouseState_.rgbButtons[mouceCode])
		{
			return true;
		}
		return false;
	}

	bool IsMouceUpDown(int mouceCode)
	{
		//今は押してて、前回は押してない + 押されてて、今離した
		if (prevMouseState_.rgbButtons[mouceCode] != mouseState_.rgbButtons[mouceCode])
		{
			return true;
		}
		return false;
	}

	XMFLOAT3 GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMFLOAT3((float)x, (float)y, 0);
	}

	//コントローラー
	bool IsController(int controllerCode, int controllerID)
	{
		if (controllerState_[controllerID].Gamepad.wButtons & controllerCode)
		{
			return TRUE; //押してる
		}
		return FALSE; //押してない
	}

	bool IsControllerDown(int controllerCode, int controllerID)
	{
		//今は押してて、前回は押してない
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons && controllerState_[controllerID].Gamepad.wButtons == controllerCode)
		{
			return true;
		}
		return false;
	}

	bool IsControllerUp(int controllerCode, int controllerID)
	{
		//押されてて、今離した
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons && prevControllerState_[controllerID].Gamepad.wButtons == controllerCode)
		{
			return true;
		}
		return false;
	}

	bool IsControllerUpDown(int controllerCode, int controllerID)
	{
		//今は押してて、前回は押してない + 押されてて、今離した
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons)
		{
			return true;
		}
		return false;
	}

	//ズレを直す
	float GetAnalogValue(int value, int max, int deadZone)
	{
		float result = (float)value;
		if (result > 0)
		{
			//+の場合
			if (result < deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result - deadZone) / (max - deadZone);
			}
		}

		else
		{
			//-の場合
			if (result > -deadZone)
			{
				result = 0;
			}
			else
			{
				result = (result + deadZone) / (max - deadZone);
			}
		}

		return result;
	}

	//左スティックを傾ける
	XMFLOAT3 GetPadStickL(int controllerID)
	{
		float x = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbLX, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbLY, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//右スティックを傾ける
	XMFLOAT3 GetPadStickR(int controllerID)
	{
		float x = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbRX, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbRY, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//左スティックを押す
	float GetPadTrrigerL(int controllerID)
	{
		return GetAnalogValue(controllerState_[controllerID].Gamepad.bLeftTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//右スティックを押す
	float GetPadTrrigerR(int controllerID)
	{
		return GetAnalogValue(controllerState_[controllerID].Gamepad.bRightTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	void Release()
	{
		SAFE_RELEASE(pMouseDevice_);
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pDInput);
	}
}