/*============================================================
*	@file	 : Sky.cpp
*	@brief	 : スカイドーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/06
*============================================================*/
#include "Sky.h"
#include "ModelRenderer.h"
#include "Game.h"
#include "Camera.h"

void Sky::Initialize()
{
	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 100.0f, 100.0f, 100.0f }
	);

	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\sky.obj")->LoadShader("Unlit");
}

void Sky::Finalize()
{
	GameObject::Finalize();
}

void Sky::Update(double deltaTime)
{
	Camera* camera = Game::GetGameObject<Camera>();

	mTransform.SetPosition(camera->GetPosition());

	GameObject::Update(deltaTime);
}

void Sky::Draw() const
{
	GameObject::Draw(); // 継承元のDrawを呼び出す
}