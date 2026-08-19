/*============================================================
*	@file	 : Camera.cpp
*	@brief	 : カメラオブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/08/06
*============================================================*/
#include "Camera.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "BufferManager.h"
#include "Config.h"

using namespace DirectX;

void Camera::Initialize()
{
	mTransform.SetPosition({ 0.0f, 5.0f, -10.0f });

	mTarget = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Finalize()
{
	GameObject::Finalize();
}

void Camera::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	Player* player = Game::GetGameObject<Player>();
	Vector3 playerPos = player->GetTransform().GetPosition();

	Vector3 rotation = mTransform.GetRotation();

	if (Input::GetKeyPress(VK_LEFT)) {
		mTransform.SetRotation({ rotation.x, rotation.y -= 3.0f * dt, rotation.z });
	}
	else if (Input::GetKeyPress(VK_RIGHT)) {
		mTransform.SetRotation({ rotation.x, rotation.y += 3.0f * dt, rotation.z });
	}

	rotation = mTransform.GetRotation();

	float t = 0.1f;
	mTarget = mTarget * (1.0f - t) + (playerPos + Vector3(0.0f, 2.0f, 0.0f)) * t;
	mTransform.SetPosition(mTarget + Vector3(-sinf(rotation.y) * 10.0f, 5.0f, -cosf(rotation.y) * 10.0f));

	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	mViewMatrix = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*)&mTransform.GetPosition()),
		XMLoadFloat3((XMFLOAT3*)&mTarget), XMLoadFloat3(&up));
}

Vector3 Camera::GetForward() const
{
	Vector3 forward = mTarget - mTransform.GetPosition();
	forward.Normalize();

	return forward;
}

Vector3 Camera::GetRight() const
{
	Vector3 forward = GetForward();
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Vector3 right = Vector3::Cross(up, forward);
	right.Normalize();

	return right;
}

void Camera::SetMatrix() const
{
	// プロジェクション行列設定
	XMMATRIX projection = XMMatrixPerspectiveFovLH(1.0f,
		static_cast<float>(Screen::WIDTH) / static_cast<float>(Screen::HEIGHT), 1.0f, 1000.0f);
	D3D11::BufferManager::getInstance().SetProjectionMatrix(projection);

	// ビュー行列設定
	D3D11::BufferManager::getInstance().SetViewMatrix(mViewMatrix);
}