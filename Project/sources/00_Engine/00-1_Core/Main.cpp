/*============================================================
*	@file	 : Main.cpp
*	@brief	 : メイン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/08/04
*============================================================*/
// System
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "Application.h"

#include "SceneManager.h"
#include "Debugger.h"

/*------------------------------------------------------------
	メイン
------------------------------------------------------------*/
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// 未使用パラメータ明示（警告を消去）
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// DPIスケーリング対策
	SetProcessDPIAware();

	// ウィンドウ初期化
	System::Window::getInstance().Initialize(hInstance);

	SceneManager::getInstance().Initialize();

#ifndef NDEBUG
	Debugger::getInstance().Initialize(System::Window::getInstance().GetHandle());
#endif

	// ウィンドウ表示
	System::Window::getInstance().Show(nCmdShow);

	// タイマー初期化
	System::Timer::getInstance().Initialize();

	// ゲームループ
	int isQuit = Application::getInstance().Run();

	timeEndPeriod(1);

#ifndef NDEBUG
	Debugger::getInstance().Finalize();
#endif

	SceneManager::getInstance().Finalize();	

	return isQuit;
}