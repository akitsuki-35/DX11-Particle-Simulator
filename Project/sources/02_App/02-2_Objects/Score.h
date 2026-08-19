/*============================================================
*	@file	 : Score.h
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "GameObject.h"

/*============================================================
*	@class	: Score
*	@brief	: スコア
*============================================================*/
class Score : public GameObject
{
private:
	int mValue{};
	static constexpr int DIGIT{ 2 };

public:
	Score() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	void Add(int value) { mValue += value; }
};