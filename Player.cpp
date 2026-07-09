/*============================================================
*	@file	 : Player.cpp
*	@brief	 : プレイヤー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/07/09
*============================================================*/
#include "Main.h"
#include "Input.h"
#include "Renderer.h"
#include "ModelRenderer.h"
#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "Bullet.h"

#include "Tree.h"
#include "Box.h"

void Player::Initialize()
{
	mLayer = 1;

	mPosition = { 0.0f, 0.0f, 0.0f };
	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 50.0f, 0.0f, 50.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\player.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Player::Finalize()
{
	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();

	GameObject::Finalize();
}

void Player::Update()
{
	float dt = 1.0f / 60.0f; // 経過時間
	float j = 15.0f; // ジャンプ力
	float g = 30.0f; // 重力加速度
	float r = 5.0f; // 抵抗力

	Vector3 oldPosition = mPosition; // プレイヤー移動前座標

	Camera* camera = Game::GetGameObject<Camera>();
	Vector3 forward = camera->GetForward();
	Vector3 right = camera->GetRight();

	forward.y = 0.0f;
	forward.Normalize();

	right.y = 0.0f;
	right.Normalize();

	// キー入力移動処理
	if (Input::GetKeyPress('D')) {
		mVelocity += right * 50.0f * dt;
	}
	if (Input::GetKeyPress('A')) {
		mVelocity -= right * 50.0f * dt;
	}
	if (Input::GetKeyPress('W')) {
		mVelocity += forward * 50.0f * dt;
	}
	if (Input::GetKeyPress('S')) {
		mVelocity -= forward * 50.0f * dt;
	}

	mRotation.y = atan2f(mVelocity.x, mVelocity.z);

	// ジャンプ
	if (mGround) {
		if (Input::GetKeyTrigger('K')) {
			mVelocity.y += j; // 撃力

			// スケールアニメーション
			mScale.y = 2.0f;
			mScale.x = 0.75f;
			mScale.z = 0.75f;
		}
	}

	// スケールを元に戻す
	mScale.x += (1.0f - mScale.x) * 0.1f;
	mScale.y += (1.0f - mScale.y) * 0.1f;
	mScale.z += (1.0f - mScale.z) * 0.1f;

	// 重力加速度
	mVelocity.y += -g * dt;

	// 摩擦抵抗
	mVelocity.x += -mVelocity.x * r * dt;
	mVelocity.z += -mVelocity.z * r * dt;

	// 移動処理
	mPosition += mVelocity * dt;

	bool oldGround = mGround;
	mGround = false;

	// 地面との衝突判定
	if (mPosition.y < 0.0f) {
		mPosition.y = 0.0f;
		mVelocity.y = 0.0f;
		mGround = true;
	}

	// 木との衝突判定
	auto trees = Game::GetGameObjects<Tree>();
	for (auto tree : trees) {
		Vector3 treePosition = tree->GetPosition();
		Vector3 playerPosition = mPosition;

		treePosition.y = 0.0f;
		playerPosition.y = 0.0f;
		Vector3 dir = playerPosition - treePosition; // 方向ベクトル算出
		float length = dir.Length(); // 距離計算

		if (length < 1.5f) {
			dir /= length; // 正規化
			dir *= 1.5f - length;

			mPosition += dir;
		}
	}

	// 箱との衝突判定
	auto boxes = Game::GetGameObjects<Box>();
	for (auto box : boxes) {
		Vector3 boxPosition = box->GetPosition();
		Vector3 boxScale = box->GetScale();

		if (boxPosition.x - boxScale.x < mPosition.x &&
			mPosition.x < boxPosition.x + boxScale.x &&
			boxPosition.z - boxScale.z < mPosition.z &&
			mPosition.z < boxPosition.z + boxScale.z) 
		{
			if (boxPosition.y + boxScale.y < mPosition.y &&
				mPosition.y < boxPosition.y + boxScale.y * 2.0f &&
				mVelocity.y < 0.0f)
			{
				mPosition.y = boxPosition.y + boxScale.y * 2.0f;
				mVelocity.y = 0.0f;
				mGround = true;
			}
			else if (boxPosition.y - boxScale.y < mPosition.y &&
				mPosition.y < boxPosition.y + boxScale.y)
			{
				mPosition.x = oldPosition.x + mScale.x;
				mPosition.z = oldPosition.z + mScale.z;

				mVelocity.x = 0.0f;
				mVelocity.z = 0.0f;
			}
		}
	}

	if (!oldGround && mGround) {
		// スケールアニメーション
		mScale.y = 0.5f;
		mScale.x = 1.5f;
		mScale.z = 1.5f;
	}

	// スケールを元に戻す
	mScale.x += (1.0f - mScale.x) * 0.1f;
	mScale.y += (1.0f - mScale.y) * 0.1f;
	mScale.z += (1.0f - mScale.z) * 0.1f;

	// 弾の発射
	if (Input::GetKeyTrigger('J')) {

		Bullet* bullet = Game::AddGameObject<Bullet>();
		bullet->SetPosition({ mPosition.x, mPosition.y, mPosition.z });
		bullet->SetVelocity(GetForward() * 50.0f);
	}
	
	// 移動アニメーション
	if (mGround) {
		mMoveAnimation += mVelocity.Length() * dt;
		mScale.y += sinf(mMoveAnimation * 3.0f) * 0.03f;
	}

	GameObject::Update();
}

void Player::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(_mVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(_mPixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(mScale.x, mScale.y, mScale.z); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y + XM_PI, mRotation.z); // 回転
	t = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	GameObject::Draw(); // 継承元のDrawを呼び出す
}