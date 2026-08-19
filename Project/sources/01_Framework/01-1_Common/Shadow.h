/*============================================================
*	@file	 : Shadow.h
*	@brief	 : シャドウ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Shadow
*	@brief	: シャドウ
*============================================================*/
class Shadow: public GameObject
{
public:
	Shadow() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};