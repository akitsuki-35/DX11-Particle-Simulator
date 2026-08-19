/*============================================================
*	@file	 : Box.cpp
*	@brief	 : 箱
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/08/06
*============================================================*/
#include "Box.h"
#include "ModelRenderer.h"

void Box::Initialize()
{
	mTransform = Transform(
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	);

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->LoadModel("assets\\models\\box.obj")->LoadShader("Directional");

	// シェーダー読込
}

void Box::Finalize()
{
	GameObject::Finalize();
}

void Box::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Box::Draw() const
{
	GameObject::Draw(); // 継承元のDrawを呼び出す
}
