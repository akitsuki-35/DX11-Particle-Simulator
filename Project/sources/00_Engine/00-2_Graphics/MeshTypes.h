/*============================================================
*	@file	 : MeshTypes.h
*	@brief	 : メッシュタイプ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/26
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Elements.h"
#include <array>

/*============================================================
*	@namespace	: MeshType
*	@brief		: メッシュタイプのユーティリティ定義
*============================================================*/
namespace MeshType {
/*--------------------------------------------------
	板ポリゴン
----------------------------------------------------*/
	namespace Plane {

		// メッシュピボット列挙体
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

		// メッシュ方向列挙体
		enum class Axis  : uint8_t
		{
			XY,
			XZ,
			YZ,
			
			Count
		};

		struct DESC
		{
			Pivot pivot = Pivot::Center;
			Axis axis = Axis::XZ;
		};

		// 板ポリゴン生成
		std::array<Element::VERTEX3D, 4> Create(const DESC& desc);
	}
}