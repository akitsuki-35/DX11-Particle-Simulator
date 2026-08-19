/*============================================================
*	@file	 : ParticleRenderer.cpp
*	@brief	 : パーティクル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#include "ParticleRenderer.h"
#include "ParticleEmitter.h"
#include "BufferManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Scene.h"

using namespace DirectX;

void ParticleRenderer::Draw() const
{
	if (!_mEmitter || !_mTexture) {
		return;
	}

	Camera* camera = Scene::GetGameObject<Camera>();

	if (!camera) {
		return;
	}

	// カメラ距離計算
	CalcCameraZ(camera->GetPosition(), camera->GetForward());

	Renderer::Begin();

	Bind();
	_mTexture->Bind();

	D3D11::BufferManager::getInstance().SetWorldMatrix(_mEmitter->GetTransform().GetWorldMatrix());

	// ビュー行列取得
	XMMATRIX view = camera->GetViewMatrix();

	// ビルボード用回転行列取得
	XMMATRIX r = _mEmitter->GetTransform().createBillboardRotation(view);

	// マテリアル設定
	Element::MATERIAL material{};
	material.Diffuse = mColor;
	material.TextureEnable = static_cast<bool>(_mTexture != nullptr);
	D3D11::BufferManager::getInstance().SetMaterial(material);

	// 有効パーティクル個数
	for (int i = 0; i < _mEmitter->PARTICLE_MAX; i++) {
		if (_mEmitter->mParticles[i].mEnable) {

			_mEmitter->mParticles[i].mMesh.Bind();

			// マトリクス設定
			XMMATRIX w{}, s{}, t{};

			// 拡大縮小	
			s = XMMatrixScaling(_mEmitter->mParticles[i].mScale.x, _mEmitter->mParticles[i].mScale.y,
				_mEmitter->mParticles[i].mScale.z);

			// 平行移動
			t = XMMatrixTranslation(_mEmitter->mParticles[i].mPosition.x,
				_mEmitter->mParticles[i].mPosition.y, _mEmitter->mParticles[i].mPosition.z);
			
			w = s * r * t;

			D3D11::BufferManager::getInstance().SetWorldMatrix(w);

			// 描画
			_mEmitter->mParticles[i].mMesh.Draw();
		}
	}

	Renderer::End();
}

DirectX::XMMATRIX ParticleRenderer::getWorldMatrix() const
{
	Camera* camera = Scene::GetGameObject<Camera>();
	return _mOwner->GetTransform().GetBillboardMatrix(camera->GetViewMatrix());
}

ParticleRenderer* ParticleRenderer::LoadTexture(const char* fileName)
{
	_mTexture = TextureManager::getInstance().Load(fileName);
	return this;
}
