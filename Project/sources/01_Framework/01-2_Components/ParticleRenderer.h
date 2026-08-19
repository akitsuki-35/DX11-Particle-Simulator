/*============================================================
*	@file	 : ParticleRenderer.h
*	@brief	 : パーティクル描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/15
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "Renderer.h"
#include "Elements.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: ParticleRenderer
*	@brief	: パーティクル描画コンポーネント
*============================================================*/
class ParticleRenderer : public Renderer
{
	friend class ParticleEmitter;

private:
	// エミッタ
	ParticleEmitter* _mEmitter{ nullptr };

	// テクスチャ
	Texture* _mTexture{ nullptr };

public:
	ParticleRenderer(GameObject* owner)
		: Renderer(owner) {
		// 不透明レイヤーに描画
		mSortKey.layer = Layer::Alpha;
	};

	~ParticleRenderer() override = default;

	// エミッタのセット
	// コンポーネントのアタッチと同時に呼び出す
	ParticleRenderer* SetEmitter(ParticleEmitter* emitter) {
		_mEmitter = emitter;
		return this;
	}

	void Draw() const override;

	void Finalize() override {
		_mTexture = nullptr;
		Renderer::Finalize();
	}

private:
	// ワールド行列取得
	DirectX::XMMATRIX getWorldMatrix() const override;

public:
	// テクスチャ読み込み
	ParticleRenderer* LoadTexture(const char* fileName);

	// ゲッター
	Texture* GetTexture() const { return _mTexture; }
};