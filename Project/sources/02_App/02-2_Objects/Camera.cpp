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
#include "BufferManager.h"
#include "Config.h"

using namespace DirectX;

void Camera::Initialize()
{
	mTransform.SetPosition({ 0.0f, 0.0f, -10.0f });

	constexpr float pitch = DirectX::XMConvertToRadians(30.0f);
	constexpr float yaw = DirectX::XMConvertToRadians(-30.0f);

	mTransform.SetRotation({ pitch, yaw, 0.0f });

	mTarget = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::Finalize()
{
	GameObject::Finalize();
}

void Camera::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);
	
	Vector3 rotation = mTransform.GetRotation();

	if (Input::GetKeyPress('A')) {
		mTransform.SetRotation({ rotation.x, rotation.y -= 2.0f * dt, rotation.z });
	}
	else if (Input::GetKeyPress('D')) {
		mTransform.SetRotation({ rotation.x, rotation.y += 2.0f * dt, rotation.z });
	}
	else if (Input::GetKeyPress('S')) {
		mTransform.SetRotation({ rotation.x += 2.0f * dt, rotation.y, rotation.z });
	}
	else if (Input::GetKeyPress('W')) {
		mTransform.SetRotation({ rotation.x -= 2.0f * dt, rotation.y, rotation.z });
	}

	constexpr float maxPitch = DirectX::XMConvertToRadians(85.0f);
	if (rotation.x < -maxPitch) rotation.x = -maxPitch;
	if (rotation.x > maxPitch) rotation.x = maxPitch;

	rotation = mTransform.GetRotation();

	if (Input::GetKeyPress('I')) {
		mDistance -= 30.0f * dt;
	}
	if (Input::GetKeyPress('K')) {
		mDistance += 30.0f * dt;
	}

	if (mDistance < 2.0f)  mDistance = 2.0f;
	if (mDistance > 100.0f) mDistance = 100.0f;

	float t = 0.1f;
	mTarget = mTarget * (1.0f - t) + (Vector3(0.0f, 0.0f, 0.0f) + Vector3(0.0f, 2.0f, 0.0f)) * t;

	float cosPitch = cosf(rotation.x);
	float sinPitch = sinf(rotation.x);
	float cosYaw = cosf(rotation.y);
	float sinYaw = sinf(rotation.y);

	Vector3 cameraOffset{};
	cameraOffset.x = sinYaw * cosPitch * mDistance;
	cameraOffset.y = -sinPitch * mDistance;
	cameraOffset.z = cosYaw * cosPitch * mDistance;

	mTransform.SetPosition(mTarget - cameraOffset);

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