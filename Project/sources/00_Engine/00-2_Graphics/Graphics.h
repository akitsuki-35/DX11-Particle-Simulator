/*============================================================
*	@file	 : Graphics.h
*	@brief	 : 描画システム制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Config.h"

namespace D3D11 {
/*============================================================
*	@class	: Graphics
*	@brief	: 描画システム制御
*============================================================*/
	class Graphics final
	{
	/*--------------------------------------------------
		Singleton用
	----------------------------------------------------*/
	public:
		static Graphics& getInstance() {
			static Graphics instance;
			return instance;
		}

	private:
		Graphics() = default;
		Graphics(const Graphics&) = delete;

		Graphics& operator=(const Graphics&) = delete;
		Graphics(Graphics&&) = delete;

		Graphics& operator=(Graphics&&) = delete;
		~Graphics() {};

	/*--------------------------------------------------
		メンバ変数・メンバ関数
	----------------------------------------------------*/
	public:
		void Initialize();
		void Finalize();
		void Begin();
		void End();
		void SetViewport(float width = Screen::WIDTH, float height = Screen::HEIGHT);
	};
}