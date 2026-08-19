/*============================================================
*	@file	 : Enemy.cpp
*	@brief	 : エネミー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#include "Enemy.h"
#include "ModelRenderer.h"

void Enemy::Initialize()
{
	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\player.obj")->LoadShader("Directional");
}

void Enemy::Finalize()
{
	GameObject::Finalize();
}

void Enemy::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Enemy::Draw() const
{
	GameObject::Draw(); // 継承元のDrawを呼び出す
}
