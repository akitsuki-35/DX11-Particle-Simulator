/*============================================================
*	@file	 : SystemTimer.h
*	@brief	 : ゲーム内時間制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/07/07
*============================================================*/
#pragma once

#include <Windows.h>

namespace System {
/*============================================================
*	@class	: Timer
*	@brief	: システムタイマー
*============================================================*/
	class Timer final
	{
	/*--------------------------------------------------
		Singleton用
	----------------------------------------------------*/
	public:
		static Timer& getInstance() {
			static Timer instance;
			return instance;
		}

	private:
		Timer() = default;
		Timer(const Timer&) = delete;

		Timer& operator=(const Timer&) = delete;
		Timer(Timer&&) = delete;

		Timer& operator=(Timer&&) = delete;
		~Timer() {};

	/*--------------------------------------------------
		メンバ変数・メンバ関数
	----------------------------------------------------*/
	private:
		LARGE_INTEGER mFreq{};
		LARGE_INTEGER mExecLastTime{};
		LARGE_INTEGER mCurrentTime{};
		double mAccumulator{};
		double mFps{ 1.0 / 60.0 };

	public:
		void Initialize();
		bool Tick();
		double GetDeltaTime() const { return mFps; }
		void SetFps(double fps) { mFps = 1.0 / fps; }
	};
}