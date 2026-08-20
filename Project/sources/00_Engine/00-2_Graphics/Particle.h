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
#include "Mesh.h"

namespace ParticleType {
	class Base;
	class Box;
}

/*============================================================
*	@class	: Particle
*	@brief	: パーティクルの粒子構造体
*============================================================*/
class Particle
{
	friend class ParticleEmitter;
	friend class ParticleRenderer;

private:
	Mesh mMesh{};
	Vector3 mPosition{ 0.0f, 0.0f, 0.0f };
	Vector3 mScale{ 1.0f, 1.0f, 1.0f };
	float mAlpha{ 1.0f };

	Vector3 mVelocity{};

	bool mEnable{ false };
	int mLife{ 0 };

public:
	Particle();

	// 更新
	void Update(double deltaTime);

	// パラメータのセット
	void SetParameter(const Vector3& position, const Vector3& velocity, const Vector3& scale, int life = 60) {
		mPosition = position;
		mVelocity = velocity;
		mScale = scale;
		mLife = life;
	}

	// 有効・無効切り替え
	void Enable() { mEnable = true; }
	void Disable() { mEnable = false; }

	// 有効・無効状態取得
	bool IsEnable() const { return mEnable; }
};