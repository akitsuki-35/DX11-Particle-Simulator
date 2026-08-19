/*============================================================
*	@file	 : Grass.h
*	@brief	 : 草のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/08/06
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Grass
*	@brief	: 草のビルボード
*============================================================*/
class Grass : public GameObject
{
public:
	Grass() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};