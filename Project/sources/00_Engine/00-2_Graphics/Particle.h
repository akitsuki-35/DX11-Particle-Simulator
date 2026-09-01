/*============================================================
*	@file	 : Particle.h
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "Vector3.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
struct ParticleDesc;

/*============================================================
*	@class	: Particle
*	@brief	: パーティクルの粒子構造体
*============================================================*/
class Particle
{
	friend class ParticleEmitter;
	friend class ParticleRenderer;

private:
	Vector3 mPosition{ 0.0f, 0.0f, 0.0f };
	Vector3 mScale{ 1.0f, 1.0f, 1.0f };

	Vector3 mVelocity{};
	Vector3 mAccel{};
	float mGravity{};
	float mDrag{};

	bool mEnable{ false };
	int mLife{ 0 };

public:
	Particle() = default;

	// 更新
	void Update(double deltaTime);

	// パラメータのセット
	// positionには基本的にエミッタ本体の座標を指定する
	void SetParameter(const Vector3& position, const Vector3& velocity, const Vector3& accel, const Vector3& scale,
		const float& gravity,  const float& drag, const int& life);

	// 有効・無効切り替え
	void Enable() { mEnable = true; }
	void Disable() { mEnable = false; }

	// 有効・無効状態取得
	bool IsEnable() const { return mEnable; }
};