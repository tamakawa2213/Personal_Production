#pragma once

#include <DirectXMath.h>
#include <dInput.h>
#include "XInput.h"

#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

namespace Input
{
	extern XINPUT_STATE controllerState_;

	void Initialize(HWND hWnd);
	void Update();

	//�L�[�{�[�h
	bool IsKey(int keyCode);		//�L�[�������Ă����
	bool IsKeyDown(int keyCode);	//�L�[���������u��
	bool IsKeyUp(int keyCode);		//�L�[�𗣂����u��

	//�}�E�X
	DirectX::XMFLOAT3 GetMousePosition();	//�}�E�X�̈ʒu���擾
	void SetMousePosition(int x, int y);	//�}�E�X�̈ʒu��ݒ�
	DirectX::XMFLOAT3 GetMouseMovement();	//�}�E�X�̈ړ��ʂ��擾
	bool IsMouseMove();						//�}�E�X����������
	bool IsMouse(int mouseBotton);			//�}�E�X�������Ă����
	bool IsMouseDown(int mouseBotton);		//�}�E�X���������u��
	bool IsMouseUp(int mouseBotton);		//�}�E�X�𗣂����u��

	//�R���g���[���[
	bool IsCtrl(int ctrlBotton);				//�{�^���������Ă����
	bool IsCtrlUp(int ctrlBotton);				//�{�^���𗣂����u��
	bool IsCtrlDown(int ctrlBotton);			//�{�^�����������u��
	DirectX::XMFLOAT3 CtrlL_StickInclination();	//L�X�e�B�b�N�̌X��
	DirectX::XMFLOAT3 CtrlR_StickInclination();	//R�X�e�B�b�N�̌X��
	float CtrlTriggerInclination(BYTE Trigger);	//�g���K�[�̉������݋

	void Release();
};