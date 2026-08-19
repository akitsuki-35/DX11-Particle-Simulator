/*============================================================
*	@file	 : Texture.h
*	@brief	 : テクスチャリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/13
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include <DirectXMath.h>
#include <wrl/client.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
struct ID3D11ShaderResourceView;

/*============================================================
*	@class	: Texture
*	@brief	: テクスチャリソース
*============================================================*/
class Texture
{
	friend class TextureManager;
	friend class FontManager;
	friend class AssimpLoader;

	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

protected:
	// サイズ
	DirectX::XMUINT2 mSize{};

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _mSRV{ nullptr };

public:
	void Bind(UINT slot = 0) const;

	const DirectX::XMUINT2& GetSize() const { return mSize; }
	const UINT& GetWidth() const { return mSize.x; }
	const UINT& GetHeight() const { return mSize.y; }
	ID3D11ShaderResourceView* GetSRV() { return _mSRV.Get(); }
};