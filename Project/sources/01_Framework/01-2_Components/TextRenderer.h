/*============================================================
*	@file	 : TextRenderer.h
*	@brief	 : テキスト描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "UIRenderer.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;
class Transform;
struct Font;
struct Glyph;

/*============================================================
*	@class	: UIRenderer
*	@brief	: UI描画コンポーネント
*============================================================*/
class TextRenderer : public UIRenderer
{
private:
	Font* _mFont{}; // フォント
	std::wstring mText{}; // 表示文字列
	size_t mCharsPerLine{ 30 }; // 1行あたりの文字数

public:
	void Finalize() override {
		_mFont = nullptr;
		UIRenderer::Finalize();
	}

	TextRenderer();

	TextRenderer(GameObject* owner);

	~TextRenderer() override = default;

	void Draw() const override;

private:
	// ドロップシャドウ描画
	void shadowDraw(const Glyph* glyph, const Transform& transform) const;

	DirectX::XMFLOAT4 convertTextColor(int index) const;

	DirectX::XMMATRIX getWorldMatrix() = delete;
	Renderer* SetColor(const DirectX::XMFLOAT4 color) = delete;

public:
	UIRenderer* LoadTexture(const char* fileName) = delete;

	// フォントセット
	TextRenderer* SetFont(const std::string& fontName);

	TextRenderer* SetTextSize(const float& size);

	// テキスト更新
	TextRenderer* SetText(const std::string& text);

	// 1行あたりの文字数更新
	TextRenderer* SetCharsPerLine(const size_t& charsPerLine);
};