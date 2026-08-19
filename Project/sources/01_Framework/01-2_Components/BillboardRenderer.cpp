/*============================================================
*	@file	 : BillboardRenderer.cpp
*	@brief	 : ビルボード描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "BillboardRenderer.h"
#include "Scene.h"
#include "Camera.h"

DirectX::XMMATRIX BillboardRenderer::getWorldMatrix() const
{
	Camera* camera = Scene::GetGameObject<Camera>();
	return _mOwner->GetTransform().GetBillboardMatrix(camera->GetViewMatrix());
}
