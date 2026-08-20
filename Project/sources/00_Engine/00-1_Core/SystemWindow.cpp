/*============================================================
*	@file	 : SystemWindow.cpp
*	@brief	 : システムウィンドウ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/07/07
*============================================================*/
#include "SystemWindow.h"

// ImGui
#include <ImGui/imgui_impl_win32.h>
/*------------------------------------------------------------
	ローカル関数 プロトタイプ宣言
------------------------------------------------------------*/
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void System::Window::Initialize(HINSTANCE hInstance, int width, int height)
{
	mHInstance = hInstance;
	mWidth = width;
	mHeigth = height;

	// ウィンドウクラス登録
	WNDCLASSEX wcex{};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	RegisterClassEx(&wcex);

	// ウィンドウ短形
	RECT rc = { 0, 0, mWidth, mHeigth };

	// メインウィンドウ作成
	mHwnd = CreateWindowEx(
		0, 
		CLASS_NAME, 
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT,
		rc.right - rc.left, 
		rc.bottom - rc.top, 
		nullptr, 
		nullptr, 
		hInstance, 
		nullptr
	);

	(void)CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	// タイトルバーと枠を削除
	SetWindowLongPtr(mHwnd, GWL_STYLE, WS_POPUP);

	// 疑似フルスクリーン化
	SetWindowPos(
		mHwnd, 
		HWND_TOP, 
		0, 0,
		mWidth, mHeigth, 
		SWP_FRAMECHANGED | SWP_NOZORDER);
}

void System::Window::Finalize() const
{
	DestroyWindow(mHwnd);
	UnregisterClass(CLASS_NAME, mHInstance);
	CoUninitialize();
}

void System::Window::Show(int nCmdShow) const
{
	ShowWindow(mHwnd, nCmdShow);
	UpdateWindow(mHwnd);
}

int System::Window::ProcessMessage() const
{
	// メッセージループ
	MSG msg{};

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return true;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT System::Window::wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	// ウィンドウプロシージャ
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}