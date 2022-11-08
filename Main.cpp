//�C���N���[�h
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "Engine/Direct3D.h"
#include "Engine/Texture.h"
#include "Engine/Camera.h"
#include "Engine/CallDef.h"
#include "Engine/Transform.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/RootJob.h"

#pragma comment(lib, "winmm.lib")

//�萔�錾
LPCWSTR WIN_CLASS_NAME = L"SampleGame";	//�E�B���h�E�N���X��
const unsigned int WINDOW_WIDTH = 1200;	//�E�B���h�E�̕�
const unsigned int WINDOW_HEIGHT = 600;	//�E�B���h�E�̍���

RootJob* pRootJob;

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g(�v���O�����̃X�^�[�g�n�_)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	//�E�B���h�E�N���X(�݌v�})���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);				//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;					//�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;			//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;					//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;			//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;						//���j���[
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j

	RegisterClassEx(&wc);  //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;	//�E�B���h�E��
	int winH = winRect.bottom - winRect.top;	//�E�B���h�E����

	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//�E�B���h�E�N���X��
		L"�l����",		//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW,	//�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,			//�\���ʒu���i���܂����j
		CW_USEDEFAULT,			//�\���ʒu��i���܂����j
		winW,					//�E�B���h�E��
		winH,					//�E�B���h�E����
		NULL,					//�e�E�C���h�E�i�Ȃ��j
		NULL,					//���j���[�i�Ȃ��j
		hInstance,				//�C���X�^���X
		NULL					//�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;

	//COM(Component Object Model)�̏�����
	hr = CoInitialize(nullptr);
	if (FAILED(hr)) {
		CoUninitialize();
		PostQuitMessage(0);
	}

	//Direct3D������
	hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
	if (FAILED(hr)) {
		Direct3D::Release();
		PostQuitMessage(0);
	}

	//RootJob������
	pRootJob = nullptr;
	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();

	//DirectInput�̏�����
	Input::Initialize(hWnd);

	//�J�����̏�����
	Camera::Initialize(winW, winH);

	//���b�Z�[�W���[�v(�����N����̂�҂�)
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			timeBeginPeriod(1);	//timeEndPeriod�ƃZ�b�g�Ŏg�p����֐�
			static DWORD countFps = 0;
			static DWORD startTime = timeGetTime();	//timeGetTime() = ���݂̎��Ԃ�Ԃ��֐�
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if (nowTime - startTime >= 1000)
			{
				WCHAR str[16];
				wsprintf(str, L"%u", countFps);
				SetWindowText(hWnd, str);
				countFps = 0;
				startTime = nowTime;
			}

			if ((nowTime - lastUpdateTime) * 60 <= 1000.0f)
			{
				continue;
			}
			lastUpdateTime = nowTime;

			countFps++;

			WCHAR str[16];
			wsprintf(str, L"%u", countFps);
			//SetWindowText(hWnd, str);

			//�Q�[���̏���
			pRootJob->Update();
			Camera::Update();
			Direct3D::BeginDraw();

			//���͏��̍X�V
			Input::Update();
			pRootJob->UpdateSub();

			//�`�揈��
			pRootJob->DrawSub();

			Direct3D::EndDraw();

			timeEndPeriod(1);
		}
	}
	pRootJob->ReleaseSub();
	SAFE_DELETE(pRootJob);
	Input::Release();
	Model::Release();
	Direct3D::Release();
	CoUninitialize();	//COM��Release
	return 0;
}

//�E�B���h�E�v���V�[�W��(�������������ɌĂяo�����֐�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}