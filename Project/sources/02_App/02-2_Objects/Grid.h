/*============================================================
*	@file	 : Grid.h
*	@brief	 : グリッド
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/20
*	@updated : 2026/08/20
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Grid
*	@brief	: グリッド
*============================================================*/
class Grid : public GameObject
{
public:
	Grid() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};