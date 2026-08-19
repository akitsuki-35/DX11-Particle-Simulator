/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Tree
*	@brief	: 木のビルボード描画
*============================================================*/
class Tree : public GameObject
{
public:
	Tree() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};