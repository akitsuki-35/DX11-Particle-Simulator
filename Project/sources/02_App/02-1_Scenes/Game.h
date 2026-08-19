/*============================================================
*	@file	 : Game.h
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Scene.h"
#include <list>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class GameObject;

/*============================================================
*	@class	: Game
*	@brief	: ゲームシーン（Sceneを継承）
*============================================================*/
class Game : public Scene
{
private:
	static std::list<GameObject*> gameObjects;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};