/*============================================================
*	@file	 : Debugger.h
*	@brief	 : ImGuiデバッガー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/21
*	@updated : 2026/08/19
*============================================================*/
#pragma once

#ifndef NDEBUG

#include <Windows.h>

/*============================================================
*	@class	: Debugger
*	@brief	: デバッガークラス
*
* 　※Initialize, Fainalize, Draw変更厳禁！！
*============================================================*/
class Debugger
{
	Debugger() = delete;

public:
	// 初期化～描画
	static const void Initialize(HWND hwnd);
	static const void Finalize();
	static const void Update();
	static const void Draw();
};
#endif