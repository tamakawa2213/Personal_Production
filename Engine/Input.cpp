#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256] = { 0 };
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;
	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevMouseState_;
	XMFLOAT3 mousePosition;

	//�R���g���[��
	const int MAX_NUM = 4;
	XINPUT_STATE controllerState_[MAX_NUM];
	XINPUT_STATE prevControllerState_[MAX_NUM];

	HRESULT Initialize(HWND hWnd)
	{
		HRESULT hr = DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�C���v�b�g�Ɏ��s���܂���", L"�G���[", MB_OK);
			SAFE_RELEASE(pDInput);
			return hr;
		}
		hr = pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�L�[�{�[�h�̎擾�Ɏ��s���܂���", L"�G���[", MB_OK);
			SAFE_RELEASE(pDInput);
			return hr;
		}
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		hr = pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�}�E�X�̎擾�Ɏ��s���܂���", L"�G���[", MB_OK);
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

	//�L�[�{�[�h
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
		//���͉����ĂāA�O��͉����ĂȂ�
		if (prevKeyState[keyCode] != keyState[keyCode] && keyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//������ĂāA��������
		if (prevKeyState[keyCode] != keyState[keyCode] && prevKeyState[keyCode])
		{
			return true;
		}
		return false;
	}

	bool IsKeyUpDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ� + ������ĂāA��������
		if (prevKeyState[keyCode] != keyState[keyCode])
		{
			return true;
		}
		return false;
	}

	//�}�E�X
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
		//���͉����ĂāA�O��͉����ĂȂ�
		if (prevMouseState_.rgbButtons[mouceCode] != mouseState_.rgbButtons[mouceCode] && mouseState_.rgbButtons[mouceCode])
		{
			return true;
		}
		return false;
	}

	bool IsMouceUp(int mouceCode)
	{
		//������ĂāA��������
		if (prevMouseState_.rgbButtons[mouceCode] != mouseState_.rgbButtons[mouceCode] && prevMouseState_.rgbButtons[mouceCode])
		{
			return true;
		}
		return false;
	}

	bool IsMouceUpDown(int mouceCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ� + ������ĂāA��������
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

	//�R���g���[���[
	bool IsController(int controllerCode, int controllerID)
	{
		if (controllerState_[controllerID].Gamepad.wButtons & controllerCode)
		{
			return TRUE; //�����Ă�
		}
		return FALSE; //�����ĂȂ�
	}

	bool IsControllerDown(int controllerCode, int controllerID)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons && controllerState_[controllerID].Gamepad.wButtons == controllerCode)
		{
			return true;
		}
		return false;
	}

	bool IsControllerUp(int controllerCode, int controllerID)
	{
		//������ĂāA��������
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons && prevControllerState_[controllerID].Gamepad.wButtons == controllerCode)
		{
			return true;
		}
		return false;
	}

	bool IsControllerUpDown(int controllerCode, int controllerID)
	{
		//���͉����ĂāA�O��͉����ĂȂ� + ������ĂāA��������
		if (prevControllerState_[controllerID].Gamepad.wButtons != controllerState_[controllerID].Gamepad.wButtons)
		{
			return true;
		}
		return false;
	}

	//�Y���𒼂�
	float GetAnalogValue(int value, int max, int deadZone)
	{
		float result = (float)value;
		if (result > 0)
		{
			//+�̏ꍇ
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
			//-�̏ꍇ
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

	//���X�e�B�b�N���X����
	XMFLOAT3 GetPadStickL(int controllerID)
	{
		float x = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbLX, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbLY, 32767, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//�E�X�e�B�b�N���X����
	XMFLOAT3 GetPadStickR(int controllerID)
	{
		float x = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbRX, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		float y = GetAnalogValue(controllerState_[controllerID].Gamepad.sThumbRY, 32767, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		return XMFLOAT3(x, y, 0);
	}

	//���X�e�B�b�N������
	float GetPadTrrigerL(int controllerID)
	{
		return GetAnalogValue(controllerState_[controllerID].Gamepad.bLeftTrigger, 255, XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	//�E�X�e�B�b�N������
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