/*============================================================
*	@file	 : GridRenderer.h
*	@brief	 : グリッド描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/20
*	@updated : 2026/08/20
*============================================================*/
#pragma once

#include "Renderer.h"
#include <wrl/client.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
struct ID3D11Buffer;
class Texture;

/*============================================================
*	@class	: GridRenderer
*	@brief	: グリッド描画コンポーネント
*============================================================*/
class GridRenderer : public Renderer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
	int mVertexCount{};

	// テクスチャ
	Texture* _mTexture{ nullptr };

public:
	GridRenderer(GameObject* owner)
		: Renderer(owner) {
		// 最背面に描画
		mSortKey.layer = Layer::Grid;
	};

	~GridRenderer() override = default;

	void Set(int xCount, int zCount, float size);
	void Draw() const override;

private:
	// ワールド行列取得
	DirectX::XMMATRIX getWorldMatrix() const override;
};