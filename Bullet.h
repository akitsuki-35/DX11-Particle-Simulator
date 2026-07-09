/*============================================================
*	@file	 : Bullet.h
*	@brief	 : 弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/06/02
*============================================================*/
#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

/*============================================================
*	@class	: Bullet
*	@brief	: 弾
*============================================================*/
class Bullet : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };
	float mLifeTime{ 2.0f };

	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

public:
	Bullet() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	void SetVelocity(const Vector3& velocity) { mVelocity = velocity; }
};

#endif // BULLET_H