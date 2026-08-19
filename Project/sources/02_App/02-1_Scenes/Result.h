/*============================================================
*	@file	 : Result.h
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "Scene.h"
#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: Result
*	@brief	: リザルトシーン（Sceneを継承）
*============================================================*/
class Result : public Scene
{
private:
	Texture* _mTexture{ nullptr };

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};