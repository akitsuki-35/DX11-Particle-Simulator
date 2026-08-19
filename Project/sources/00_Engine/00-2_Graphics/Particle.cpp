/*============================================================
*	@file	 : Particle.cpp
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "Particle.h"
#include "MeshTypes.h"

using namespace MeshType;

Particle::Particle()
{
	mMesh.CreatePlane(Plane::Pivot::Center, Plane::Axis::XY);
}

void Particle::update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	if (!mEnable) {
		return;
	}

	Vector3 gravity{ 0.0f, -9.8f, 0.0f };
	mVelocity += gravity * dt; // 重力
	mVelocity += mVelocity * -1.0f * dt; // 抵抗
	mPosition += mVelocity * dt;

	mLife--;

	if (mLife <= 0) {
		mEnable = false;
	}
}