/*============================================================
*	@file	 : Player.h
*	@brief	 : プレイヤー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/06/16
*============================================================*/
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

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

	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

public:
	Player() = default;
	//Player(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // PLAYER_H