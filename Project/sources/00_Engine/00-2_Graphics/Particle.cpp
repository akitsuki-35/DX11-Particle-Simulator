/*============================================================
*	@file	 : Particle.cpp
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "Particle.h"
#include "ParticleEmitter.h"

void Particle::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	if (!mEnable) {
		return;
	}

	Vector3 gravity{ 0.0f, -mGravity, 0.0f };
	mVelocity += mAccel * dt;
	mVelocity += gravity * dt; // 重力
	mVelocity += mVelocity * mDrag * dt; // 抵抗
	mPosition += mVelocity * dt;

	mLife--;

	if (mLife <= 0) {
		mEnable = false;
	}
}

void Particle::SetParameter(const Vector3& position, const Vector3& velocity, const Vector3& accel, const Vector3& scale, const float& gravity, const float& drag, const int& life)
{
	mPosition = position;
	mVelocity = velocity;
	mAccel = accel;
	mScale = scale;
	mGravity = gravity;
	mDrag = drag;
	mLife = life;
}