#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <Windows.h>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Texture.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/CallDef.h"
#include "../IntegratedEngine/Engine/GameTime.h"
#include "../IntegratedEngine/Engine/Time.h"
#include "../IntegratedEngine/Engine/Transform.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Engine/RootJob.h"
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

//定数宣言
LPCWSTR WIN_CLASS_NAME = L"PersonalProduction";	//ウィンドウクラス名
const unsigned int WINDOW_WIDTH = 1200;	//ウィンドウの幅
const unsigned int WINDOW_HEIGHT = 600;	//ウィンドウの高さ
const int MAX_FPS = 60;

RootJob* pRootJob;

//プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//エントリーポイント(プログラムのスタート地点)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned int)time(NULL));

	//ウィンドウクラス(設計図)を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);				//この構造体のサイズ
	wc.hInstance = hInstance;					//インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;			//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;					//ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;			//スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);	//小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	//マウスカーソル
	wc.lpszMenuName = NULL;						//メニュー
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）

	RegisterClassEx(&wc);  //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, TRUE);
	int winW = winRect.right - winRect.left;	//ウィンドウ幅
	int winH = winRect.bottom - winRect.top;	//ウィンドウ高さ

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//ウィンドウクラス名
		L"個人製作",		//タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW,	//スタイル（普通のウィンドウ）
		CW_USEDEFAULT,			//表示位置左（おまかせ）
		CW_USEDEFAULT,			//表示位置上（おまかせ）
		winW,					//ウィンドウ幅
		winH,					//ウィンドウ高さ
		NULL,					//親ウインドウ（なし）
		NULL,					//メニュー（なし）
		hInstance,				//インスタンス
		NULL					//パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;

	//COM(Component Object Model)の初期化
	hr = CoInitialize(nullptr);
	if (FAILED(hr)) {
		CoUninitialize();
		PostQuitMessage(0);
	}

	//Direct3D初期化
	hr = Direct3D::Initialize(WINDOW_WIDTH, (winH + WINDOW_HEIGHT * 2) / 3, hWnd);
	if (FAILED(hr)) {
		Direct3D::Release();
		PostQuitMessage(0);
	}

	{//GUI初期化
#if _DEBUG
		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(Direct3D::pDevice, Direct3D::pContext);
		ImGui::SetNextWindowSize(ImVec2(320, 100));
#endif
	}

	//RootJob初期化
	std::unique_ptr<RootJob> pRootJob = nullptr;
	pRootJob = std::make_unique<RootJob>(nullptr);
	pRootJob->Initialize();

	//DirectInputの初期化
	Input::Initialize(hWnd);

	//カメラの初期化
	Camera::Initialize(winW, winH);

	//メッセージループ(何か起きるのを待つ)
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			timeBeginPeriod(1);	//timeEndPeriodとセットで使用する関数
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			if ((nowTime - lastUpdateTime) * MAX_FPS <= 1000.0f)
			{
				continue;
			}

#if _DEBUG
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			//{
			//	static float f = 0.0f;
			//	static int counter = 0;

			//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

			//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			//		counter++;
			//	ImGui::SameLine();
			//	ImGui::Text("counter = %d", counter);

			//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//	ImGui::End();
			//}
			//if (show_another_window)
			//{
			//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			//	ImGui::Text("Hello from another window!");
			//	if (ImGui::Button("Close Me"))
			//		show_another_window = false;
			//	ImGui::End();
			//}
#endif

			lastUpdateTime = nowTime;

			static char DrawRange = VP_LEFT;
			{
				//spaceキーを押したら描画変更
				if (Input::Mouse::Down(DIK_SPACE))
				{
					switch (Direct3D::SplitScrMode)
					{
					case SCREEN_FULL:
						Direct3D::SplitScrMode = SCREEN_SPLIT_2;
						break;
					case SCREEN_SPLIT_2:
						if (Input::Mouse::GetPosition().x < winW / 2)	//マウスカーソルの位置でカメラの位置を決定
						{
							DrawRange = VP_LEFT;
						}
						else
						{
							DrawRange = VP_RIGHT;
						}
						Direct3D::SplitScrMode = SCREEN_FULL;
						break;
					default: break;
					}
				}
			}

			Time::Update();

			GameTime::Update();


			//ゲームの処理
			if (GameTime::IsStop())
			{
				Input::Update();
			}
			else
			{
				while (GameTime::RemainingTimes() >= 0)
				{
					//入力情報の更新
					Input::Update();

					pRootJob->Update();
					pRootJob->UpdateSub();
					GameTime::UpDated();
				}
			}
			pRootJob->FixedUpdate();
			pRootJob->FixedUpdateSub();

			Direct3D::BeginDraw();

			XMVECTOR campos[2] = { {-10.0f, 5.5f, 1.2f, 0}, {1.6f, 6, 1.5f, 0} };
			XMVECTOR camtar[2] = { {-10, 0, 1.3f, 0}, {1.5f, 0, 1.5f, 0} };


			//描画処理
			switch (Direct3D::SplitScrMode)
			{
			case SCREEN_FULL:
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
				break;
			case SCREEN_SPLIT_2:
				if (Input::Mouse::GetPosition().x < winW / 2)
				{
					//右画面描画
					{
						Direct3D::SetViewPort(VP_RIGHT);
						Camera::SetPosition(campos[1]);
						Camera::SetTarget(camtar[1]);

						Camera::Update();
						//全オブジェクトを描画
						//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
						pRootJob->DrawSub();
					}

					//左画面描画
					{
						Direct3D::SetViewPort(VP_LEFT);
						Camera::SetPosition(campos[0]);
						Camera::SetTarget(camtar[0]);

						Camera::Update();
						//全オブジェクトを描画
						//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
						pRootJob->DrawSub();
					}
				}
				else
				{
					//左画面描画
					{
						Direct3D::SetViewPort(VP_LEFT);
						Camera::SetPosition(campos[0]);
						Camera::SetTarget(camtar[0]);

						Camera::Update();
						//全オブジェクトを描画
						//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
						pRootJob->DrawSub();
					}
					//右画面描画
					{
						Direct3D::SetViewPort(VP_RIGHT);
						Camera::SetPosition(campos[1]);
						Camera::SetTarget(camtar[1]);

						Camera::Update();
						//全オブジェクトを描画
						//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
						pRootJob->DrawSub();
					}
				}
				break;
			default:
				break;
			}
			Direct3D::SetViewPort(VP_FULL);
			pRootJob->DrawUniqueSub();

#if _DEBUG
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif

			Direct3D::EndDraw();

			timeEndPeriod(1);
		}
	}
#if _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif

	pRootJob->ReleaseSub();
	Input::Release();
	Model::Release();
	Direct3D::Release();
	CoUninitialize();	//COMのRelease

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}

#if _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

//ウィンドウプロシージャ(何かあった時に呼び出される関数)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	case WM_MOUSEMOVE:
		Input::Mouse::SetPosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}

#if _DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
#endif

	return DefWindowProc(hWnd, msg, wParam, lParam);
}