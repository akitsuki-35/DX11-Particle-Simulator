/*============================================================
*	@file	 : Bullet.cpp
*	@brief	 : 弾
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/07/09
*============================================================*/
#include "Main.h"
#include "Game.h"
#include "Bullet.h"
#include "Input.h"
#include "Renderer.h"
#include "ModelRenderer.h"
#include "Enemy.h"

void Bullet::Initialize()
{
	mLayer = 1;

	mPosition = { 0.0f, 0.0f, 0.0f };
	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\bullet.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Bullet::Finalize()
{
	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();

	GameObject::Finalize();
}

void Bullet::Update()
{
	float dt = 1.0f / 60.0f;

	mPosition += mVelocity * dt;

	// 敵との衝突判定
	auto enemys = Game::GetGameObjects<Enemy>();
	for (auto enemy : enemys) {
		Vector3 dir = enemy->GetPosition() - mPosition;
		float length = dir.Length();

		if (length < 1.0f) {
			enemy->SetDestroy();
			SetDestroy();

			break;
		}
	}


	mLifeTime -= dt;
	if (mLifeTime <= 0.0f) {
		// 一定時間経過で弾を削除
		SetDestroy();
	}

	GameObject::Update();
}

void Bullet::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(_mVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(_mPixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(mScale.x, mScale.y, mScale.z); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z); // 回転
	t = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	GameObject::Draw(); // 継承元のDrawを呼び出す
}