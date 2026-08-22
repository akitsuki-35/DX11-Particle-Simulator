/*============================================================
*	@file	 : Sky.h
*	@brief	 : スカイドーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/08/06
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Sky
*	@brief	: スカイドーム
*============================================================*/
class Sky : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

public:
	Sky() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};