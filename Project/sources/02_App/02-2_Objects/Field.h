/*============================================================
*	@file	 : Field.h
*	@brief	 : フィールド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Field
*	@brief	: フィールド
*============================================================*/
class Field : public GameObject
{
public:
	Field() = default;
	
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};