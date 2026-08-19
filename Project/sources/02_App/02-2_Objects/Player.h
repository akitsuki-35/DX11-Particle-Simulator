/*============================================================
*	@file	 : Player.h
*	@brief	 : プレイヤークラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "GameObject.h"

class AudioPlayer;

/*============================================================
*	@class	: Player
*	@brief	: プレイヤー
*============================================================*/
class Player : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };
	float mRotationVel{ 0.0f };
	bool mGround{ true };
	float mMoveAnimation{ 0.0f };

	AudioPlayer* mSE{};

public:
	Player() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;
};