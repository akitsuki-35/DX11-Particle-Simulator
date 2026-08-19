/*============================================================
*	@file	 : Bullet.cpp
*	@brief	 : 弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/08/06
*============================================================*/
#include "Game.h"
#include "Bullet.h"
#include "Input.h"
#include "ModelRenderer.h"
#include "Enemy.h"

void Bullet::Initialize()
{
	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\bullet.obj")->LoadShader("Unlit");
}

void Bullet::Finalize()
{
	GameObject::Finalize();
}

void Bullet::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	Vector3 position = mTransform.GetPosition();

	position += mVelocity * dt;

	// 敵との衝突判定
	auto enemys = Game::GetGameObjects<Enemy>();
	for (auto enemy : enemys) {
		Vector3 dir = enemy->GetPosition() - position;
		float length = dir.Length();

		if (length < 1.0f) {
			enemy->SetDestroy();
			SetDestroy();

			//Game::AddGameObject<Explosion>()->SetPosition({ enemy->GetPosition().x,
			//	enemy->GetPosition().y + 1.0f, enemy->GetPosition().z });

			//Game::GetGameObject<Score>()->Add(1);

			break;
		}
	}


	mLifeTime -= dt;
	if (mLifeTime <= 0.0f) {
		// 一定時間経過で弾を削除
		SetDestroy();
	}

	mTransform.SetPosition(position);

	GameObject::Update(deltaTime);
}

void Bullet::Draw() const
{
	GameObject::Draw(); // 継承元のDrawを呼び出す
}