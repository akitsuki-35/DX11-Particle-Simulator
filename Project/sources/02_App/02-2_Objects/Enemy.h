/*============================================================
*	@file	 : Enemy.h
*	@brief	 : エネミー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Enemy
*	@brief	: エネミー
*============================================================*/
class Enemy : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

public:
	Enemy() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};