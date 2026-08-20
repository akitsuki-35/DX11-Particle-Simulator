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
private:
	Debugger() {}
	Debugger(const Debugger&);
	Debugger& operator= (const Debugger&);
	~Debugger() {};

public:
	static Debugger& getInstance() {
		static Debugger instance;
		return instance;
	}

	// ===== 初期化～描画 =====
	const void Initialize(HWND hwnd) const;
	const void Finalize() const;
	const void Update() const;
	const void Draw() const;

	// ===== デバッグウィンドウ関数をここに追加 =====
	const void BezierControl();
	const void ParticleControl();
};
#endif