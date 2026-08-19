/*============================================================
*	@file	 : Title.h
*	@brief	 : タイトルシーン
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

/*------------------------------------------------------------
	タイトルシーンの状態
------------------------------------------------------------*/
enum TitleState
{
	TITLE_FADE_IN,
	TITLE_KEYINPUT_WAIT,
	TITLE_KEYINPUT_ACTION,
	TITLE_FADE_OUT
};

/*============================================================
*	@class	: Title
*	@brief	: タイトルシーン（Sceneを継承）
*============================================================*/
class Title : public Scene
{
private:
	TitleState mState{ TitleState::TITLE_FADE_IN };
	double mAccumulatedTime{ 0.0 };
	double mKeyInputTime{};
	Texture* _mTexture{ nullptr };

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};