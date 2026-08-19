/*============================================================
*	@file	 : Application.cpp
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/07/13
*============================================================*/
#include "Application.h"
#include "SystemWindow.h"
#include "SystemTimer.h"
#include "SceneManager.h"

int Application::Run() const
{
	// アプリケーションループ
	while (1)
	{
		if (System::Window::getInstance().ProcessMessage()) {
			break;
		}
		else{
			while (System::Timer::getInstance().Tick()) {
				SceneManager::getInstance().Update(System::Timer::getInstance().GetDeltaTime());
				SceneManager::getInstance().Draw();
			}
		}
	}

    return 0;
}