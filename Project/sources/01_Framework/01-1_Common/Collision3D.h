/*============================================================
*	@file	 : Collision3D.h
*	@brief	 : 3Dコリジョンクラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/08/16
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Component.h"

namespace Collision3D {
	class Circle;
	class Box;
}

/*============================================================
*	@class	: Collision3DBase
*	@brief	: 3Dコリジョン基底クラス
*============================================================*/
class Collision3DBase : public Component
{
private:
	Vector3 mSize{};
	bool mEnable{ true };

public:
	// サイズのセット
	virtual void SetSize(const Vector3& collisionSize) { mSize = collisionSize; }

	// 有効・無効切り替え
	virtual void Enable() { mEnable = true; }
	virtual void Disable() { mEnable = false; }

	// ゲッター
	virtual const bool& IsEnabled() { return mEnable; }

	// 各種コリジョンとの当たり判定
	virtual bool IsOverlap(const Collision3D::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision3D::Box*) const { return false; }
};