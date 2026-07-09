/*============================================================
*	@file	 : Glass.h
*	@brief	 : 草のビルボード
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/06/09
*============================================================*/
#ifndef GLASS_H
#define GLASS_H

#include "GameObject.h"

/*============================================================
*	@class	: Glass
*	@brief	: 草のビルボード描画
*============================================================*/
class Glass : public GameObject
{
private:
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Glass() = default;
	Glass(const wchar_t* pFileName);

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // GLASS_H