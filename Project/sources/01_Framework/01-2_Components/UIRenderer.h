/*============================================================
*	@file	 : UIRenderer.h
*	@brief	 : UI描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "Renderer.h"
#include "UICanvas.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;
class Transform;

/*============================================================
*	@class	: UIRenderer
*	@brief	: UI描画コンポーネント
*============================================================*/
class UIRenderer : public Renderer
{
protected:
	// キャンバス
	UICanvas mCanvas{};

	// テクスチャ
	Texture* _mTexture{ nullptr };

public:
	UIRenderer() {
		// 2Dレイヤーに描画
		mSortKey.layer = Layer::UI;
	}

	UIRenderer(GameObject* owner)
		: Renderer(owner) {
		// 2Dレイヤーに描画
		mSortKey.layer = Layer::UI;
	};

	~UIRenderer() override = default;

	void Finalize() override {
		_mTexture = nullptr;
		Renderer::Finalize();
	}

	void Draw() const override;
	void Draw(const Transform& transform);

private:
	// ワールド行列取得
	DirectX::XMMATRIX getWorldMatrix() const override;

public:
	// テクスチャ読み込み
	UIRenderer* LoadTexture(const char* fileName);

	// ゲッター
	UICanvas& GetCanvas() { return mCanvas; }
	Texture* GetTexture() { return _mTexture; }
};