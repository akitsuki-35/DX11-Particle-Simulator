/*============================================================
*	@file	 : Bullet.h
*	@brief	 : 弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/08/06
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Bullet
*	@brief	: 弾
*============================================================*/
class Bullet : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };
	float mLifeTime{ 2.0f };
public:
	Bullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	void SetVelocity(const Vector3& velocity) { mVelocity = velocity; }
};