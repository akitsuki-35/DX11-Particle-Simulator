/*============================================================
*	@file	 : Config.h
*	@brief	 : システム設定・定数定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/05
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include <DirectXMath.h>

/*============================================================
*	@namespace	: Screen
*	@brief		: スクリーン関連パラメータ定義
*============================================================*/
namespace Screen {
	// 画面解像度
	static constexpr int WIDTH{ 1920 };
	static constexpr int HEIGHT{ 1080 };

	// X・Y中心座標
	static constexpr int CENTER_X{ WIDTH / 2 };
	static constexpr int CENTER_Y{ HEIGHT / 2 };

	// スクリーン端座標
	static constexpr int TOP{ 0 };
	static constexpr int BOTTOM{ HEIGHT };
	static constexpr int LEFT{ 0 };
	static constexpr int RIGHT{ WIDTH };
}

/*============================================================
*	@namespace	: Color
*	@brief		: カラー関連パラメータ定義
*============================================================*/
namespace Color {
	// カラーインデックス
	enum class Index : int
	{			   // テキスト制御文字対応
		White = 0, // = \\c[0]
		Black,	   // = \\c[1]
		Red,	   // = \\c[2]
		Green,	   // = \\c[3]
		Blue,	   // = \\c[4]
		Yellow,	   // = \\c[5]
		Purple,	   // = \\c[6]
		Cyan	   // = \\c[7]
	};

	// カラー
	static inline constexpr DirectX::XMFLOAT4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Purple = { 1.0f, 0.0f, 1.0f, 1.0f };
	static inline constexpr DirectX::XMFLOAT4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };

	inline DirectX::XMFLOAT4 ConvertColor(int index)
	{
		// カラーインデックスから色を取得
		Color::Index colorId = static_cast<Color::Index>(index);

		switch (colorId)
		{
		case Color::Index::White:
			return Color::White;

		case Color::Index::Black:
			return Color::Black;

		case Color::Index::Red:
			return Color::Red;

		case Color::Index::Green:
			return Color::Green;

		case Color::Index::Blue:
			return Color::Blue;

		case Color::Index::Yellow:
			return Color::Yellow;

		case Color::Index::Purple:
			return Color::Purple;

		case Color::Index::Cyan:
			return Color::Cyan;

		default:
			return Color::White;
		}
	}
}