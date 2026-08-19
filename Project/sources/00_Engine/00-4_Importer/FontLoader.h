/*============================================================
*	@file	 : FontLoader.h
*	@brief	 : フォントファイル読み込み
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/04
*	@updated : 2026/08/11
*============================================================*/
#pragma once

#include <dwrite.h>
#include <vector>
#include <wrl/client.h>

// フォントデータ構造体
struct Font {
	Microsoft::WRL::ComPtr<IDWriteFontFace> Face{ nullptr };
	DWRITE_FONT_METRICS Metrics{};
	float Size{ 32.0f };
};

/*============================================================
*	@class	: FontLoader
*	@brief	: フォントファイル読み込み
*============================================================*/
class FontLoader final
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// 静的な単一クラスとして扱うため、インスタンス化を禁止
	FontLoader() = delete;

public:
	static IDWriteFactory* Initialize();
	static bool Load(IDWriteFactory* factory, Font& font, const char* fontPath);
};