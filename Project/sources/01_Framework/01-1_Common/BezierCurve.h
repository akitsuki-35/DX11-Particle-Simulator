/*============================================================
*	@file	 : BezierCurve.h
*	@brief	 : ベジエ曲線
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/09
*	@updated : 2026/08/19
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Debugger.h"
#include <vector>

/*============================================================
*	@class	: BezierCurve
*	@brief	: ベジエ曲線
*============================================================*/
class BezierCurve
{
	// Debuggerから操作可能にする
	friend Debugger;

private:
	struct POINT {
		Vector3 position{};
	};

	// 指定可能な最大フレーム(初期化・参照用)
	static constexpr int DEFAULT_FRAMEMAX{ 120 };

	int mFrameMax{}; // 全体フレーム
	int mFrame{}; // 現在フレーム

	POINT mControlPoint[4]{}; // 制御点(三次ベジエ曲線)
	std::vector<POINT> mBezierPoint; // フレームごとのベジエ曲線上座標

public:
	BezierCurve();

	void Update();
	
	// ベジエ曲線上座標計算
	void CalcBezier();

	// 現在フレーム取得
	int GetFrame() const { return mFrame; }

	// 制御点座標取得
	Vector3& GetControlPoint(int index) { return mControlPoint[index].position; }

	// フレーム指定でベジエ曲線上座標取得
	Vector3& GetBezierPoint(int index) { return mBezierPoint[index].position; }

	// 最大フレーム変更
	void SetFrameMax(const int& frameMax) {
		mFrameMax = frameMax;
	}
};