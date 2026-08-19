/*============================================================
*	@file	 : Box.h
*	@brief	 : 箱
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/08/06
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Box
*	@brief	: 箱
*============================================================*/
class Box : public GameObject
{
public:
	Box() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};