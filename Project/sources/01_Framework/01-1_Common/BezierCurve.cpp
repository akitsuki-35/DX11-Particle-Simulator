/*============================================================
*	@file	 : BezierCurve.h
*	@brief	 : ベジエ曲線
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/09
*	@updated : 2026/08/19
*============================================================*/
#include "BezierCurve.h"

BezierCurve::BezierCurve()
{
	// 制御点初期化
	mControlPoint[0].position = { -15.0f, 3.0f, -15.0f };
	mControlPoint[1].position = { -30.0f, 3.0f, -30.0f };
	mControlPoint[2].position = { 30.0f, 3.0f, 30.0f };
	mControlPoint[3].position = { 15.0f, 3.0f, 15.0f };

	// フレーム0から開始
	mFrame = 0;

	// 最大フレーム定数で初期化(配列外参照防止)
	mFrameMax = DEFAULT_FRAMEMAX;
	mBezierPoint.resize(mFrameMax);

	// 曲線上座標初期化
	CalcBezier();
}

void BezierCurve::Update()
{
	// フレームをループさせる
	mFrame++;
	if (mFrame >= mFrameMax) {
		mFrame = 0;
	}
}

void BezierCurve::CalcBezier()
{
	double t;
	// 全フレームのベジエ曲線上のポイント計算
	for (int k = 0; k < mFrameMax; k++) {
		t = static_cast<double>(k) / static_cast<double>(mFrameMax - 1);

		double b0 = (1.0 - t) * (1.0 - t) * (1.0 - t);
		double b1 = 3.0 * (1.0 - t) * (1.0 - t) * t;
		double b2 = 3.0 * (1.0 - t) * t * t;
		double b3 = t * t * t;

		// x座標算出
		mBezierPoint[k].position.x = (static_cast<float>(b0) * mControlPoint[0].position.x + 
			static_cast<float>(b1) * mControlPoint[1].position.x + 
			static_cast<float>(b2) * mControlPoint[2].position.x + 
			static_cast<float>(b3) * mControlPoint[3].position.x);

		// y座標算出
		mBezierPoint[k].position.y = (static_cast<float>(b0) * mControlPoint[0].position.y + 
			static_cast<float>(b1) * mControlPoint[1].position.y + 
			static_cast<float>(b2) * mControlPoint[2].position.y + 
			static_cast<float>(b3) * mControlPoint[3].position.y);

		// z座標算出
		mBezierPoint[k].position.z = (static_cast<float>(b0) * mControlPoint[0].position.z + 
			static_cast<float>(b1) * mControlPoint[1].position.z + 
			static_cast<float>(b2) * mControlPoint[2].position.z + 
			static_cast<float>(b3) * mControlPoint[3].position.z);
	}
}
