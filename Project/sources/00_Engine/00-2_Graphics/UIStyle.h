/*============================================================
*	@file	 : UIStyle.h
*	@brief	 : UI表示スタイル設定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "Elements.h"
#include <array>

/*============================================================
*	@namespace	: UIStyle
*	@brief		: UI表示スタイルのユーティリティ定義
*============================================================*/
namespace UIStyle {
	// ピボット列挙体
	enum class Pivot : uint8_t
	{
		Center,
		CenterTop,
		CenterBottom,
		LeftTop,
		LeftBottom,
		RightTop,
		RightBottom,

		Count
	};

	std::array<Element::VERTEX3D, 4> Create(const Pivot& pivot);
}