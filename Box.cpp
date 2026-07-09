/*============================================================
*	@file	 : Box.cpp
*	@brief	 : 箱
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/06/16
*============================================================*/
#include "Main.h"
#include "Input.h"
#include "Renderer.h"
#include "ModelRenderer.h"
#include "Box.h"

void Box::Initialize()
{
	mLayer = 1;

	mPosition = { 0.0f, 0.0f, 0.0f };
	mVelocity = { 0.0f, 0.0f, 0.0f };
	mAccel = { 0.0f, 0.0f, 0.0f };

	// コンポーネント読込
	AddComponent<ModelRenderer>(this)->Load("Resources\\Models\\box.obj");

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Box::Finalize()
{
	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();

	GameObject::Finalize();
}

void Box::Update()
{
	GameObject::Update();
}

void Box::Draw() const
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
