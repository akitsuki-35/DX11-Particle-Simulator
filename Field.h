/*============================================================
*	@file	 : Field.h
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/02
*============================================================*/
#ifndef FIELD_H
#define FIELD_H

#include "GameObject.h"

/*============================================================
*	@class	: Field
*	@brief	: フィールド
*============================================================*/
class Field : public GameObject
{
private:
	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Field() = default;
	Field(const wchar_t* pFileName);
	
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // FIELD_H