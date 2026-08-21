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
/*--------------------------------------------------
		Singleton用
----------------------------------------------------*/
public:
	static Debugger& getInstance() {
		static Debugger instance;
		return instance;
	}

private:
	Debugger() = default;
	Debugger(const Debugger&) = delete;

	Debugger& operator=(const Debugger&) = delete;
	Debugger(Debugger&&) = delete;

	Debugger& operator=(Debugger&&) = delete;
	~Debugger() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
public:
	// ===== 初期化～描画 =====
	const void Initialize(HWND hwnd) const;
	const void Finalize() const;
	const void Update() const;
	const void Draw() const;

private:
	// ===== デバッグウィンドウ関数をここに追加 =====
	const void bezierControl();
	const void particleControl();
};
#endif