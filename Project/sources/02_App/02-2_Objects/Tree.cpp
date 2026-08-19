/*============================================================
*	@file	 : Tree.h
*	@brief	 : 木のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/02
*	@updated : 2026/08/04
*============================================================*/
#include "Tree.h"
#include "BillboardRenderer.h"
#include "MeshTypes.h"

using namespace MeshType;

void Tree::Initialize()
{
	BillboardRenderer* renderer = AddComponent<BillboardRenderer>(this);

	renderer->GetMesh().CreatePlane(Plane::Pivot::CenterBottom, Plane::Axis::XY);

	mTransform.SetPosition({ 0.0f,0.0f, 0.0f });
	mTransform.SetScale({ 8.0f, 10.0f, 0.0f });

	renderer->LoadTexture("assets\\textures\\tree.png")->LoadShader("Unlit");
}

void Tree::Finalize()
{
	GameObject::Finalize();
}

void Tree::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Tree::Draw() const
{
	GameObject::Draw();
}