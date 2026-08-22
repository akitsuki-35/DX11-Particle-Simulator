/*============================================================
*	@file	 : Field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/08/12
*============================================================*/
#include "Field.h"
#include "SpriteRenderer.h"
#include "MeshTypes.h"
#include "Input.h"

using namespace MeshType;

void Field::Initialize()
{
	SpriteRenderer* renderer = AddComponent<SpriteRenderer>(this);

	renderer->GetMesh().CreatePlane(Plane::Pivot::Center, Plane::Axis::XZ);
	mTransform.SetScale({ 30.0f, 30.0f, 30.0f });

	renderer->LoadTexture("assets\\textures\\glass.jpg")->LoadShader("Unlit");
}

void Field::Finalize()
{
	GameObject::Finalize();
}

void Field::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Field::Draw() const
{
	GameObject::Draw();
}