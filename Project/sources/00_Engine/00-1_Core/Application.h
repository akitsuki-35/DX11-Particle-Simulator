/*============================================================
*	@file	 : Application.h
*	@brief	 : アプリケーションループ制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/07
*	@updated : 2026/08/02
*============================================================*/
#pragma once

/*============================================================
*	@class	: Application
*	@brief	: アプリケーション
*============================================================*/
class Application final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Application& getInstance() {
		static Application instance;
		return instance;
	}

private:
	Application() = default;
	Application(const Application&) = delete;

	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;

	Application& operator=(Application&&) = delete;
	~Application() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	bool mPaused{ false }; // ポーズフラグ

public:
	int Run() const;
};