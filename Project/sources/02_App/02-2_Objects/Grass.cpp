/*============================================================
*	@file	 : Grass.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/08/06
*============================================================*/
#include "Grass.h"
#include "BillboardRenderer.h"
#include "MeshTypes.h"

using namespace MeshType;

void Grass::Initialize()
{
	BillboardRenderer* drawable = AddComponent<BillboardRenderer>(this);

	drawable->GetMesh().CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);

	mTransform.SetPosition({ 0.0f,0.0f, 0.0f });
	mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	drawable->LoadTexture("assets\\textures\\grass.png");

	drawable->LoadShader("Unlit");
}

void Grass::Finalize()
{
	GameObject::Finalize();
}

void Grass::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Grass::Draw() const
{
	GameObject::Draw();
}