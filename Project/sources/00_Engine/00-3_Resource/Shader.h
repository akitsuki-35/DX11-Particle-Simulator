/*============================================================
*	@file	 : Shader.h
*	@brief	 : シェーダーリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include <wrl/client.h>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

/*============================================================
*	@class	: Shader
*	@brief	: シェーダー・レイアウトリソース
*============================================================*/
class Shader
{
	friend class ShaderManager;
private:
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> _mVertexShader{};
	
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _mPixelShader{};

	// 頂点レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> _mLayout{};

public:
	// ゲッター
	ID3D11VertexShader* GetVertexShader() const { return _mVertexShader.Get(); }
	ID3D11PixelShader* GetPixelShader() const { return _mPixelShader.Get(); }
	ID3D11InputLayout* GetLayout() const { return _mLayout.Get(); }
};