/*============================================================
*	@file	 : TextRenderer.cpp
*	@brief	 : テキスト描画コンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#include "TextRenderer.h"
#include "Texture.h"
#include "FontLoader.h"
#include "FontManager.h"
#include "DeviceManager.h"
#include "BufferManager.h"
#include "UIStyle.h"
#include "GameObject.h"
#include "Utility.h"
#include "D3D11Config.h"
#include "Config.h"
#include <d3d11.h>
#include <dwrite.h>

using namespace DirectX;

TextRenderer::TextRenderer()
{
	// 2Dレイヤーに描画
	mSortKey.layer = Layer::UI;
	mCanvas.CreateCanvas(UIStyle::Pivot::LeftTop);
}

TextRenderer::TextRenderer(GameObject* owner)
	: UIRenderer(owner)
{
	// 2Dレイヤーに描画
	mSortKey.layer = Layer::UI;
	mCanvas.CreateCanvas(UIStyle::Pivot::LeftTop);
};

void TextRenderer::Draw() const
{
	if (mText.empty() || !_mFont) {
		return;
	}

	Renderer::Begin();

	// 深度ステート無効
	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Disable);

	// UI用設定
	Bind();
	D3D11::BufferManager::getInstance().Set2DMatrix();

	// オブジェクトのトランスフォーム取得
	Transform transform = _mOwner->GetTransform();

	// スタート位置と現在位置を初期化
	const float startX = transform.GetPosition().x;
	const float startY = transform.GetPosition().y;

	float currentX = startX;
	float currentY = startY;

	// 文字数カウント
	size_t charCount = 0;

	// 文字色
	XMFLOAT4 textColor = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };

	// 1文字ずつレンダリング処理する
	for (size_t i = 0; i < mText.length(); ++i) {
		// 1文字分の文字コード
		uint32_t codepoint = mText[i];

		// サロゲートペア（上位サロゲート）の判定と結合処理
		if (codepoint >= 0xD800 && codepoint <= 0xDBFF && (i + 1) < mText.length()) {
			uint32_t next = mText[i + 1];

			if (next >= 0xDC00 && next <= 0xDFFF)
			{
				codepoint = 0x10000 + ((codepoint - 0xD800) << 10) + (next - 0xDC00);
				++i;
			}
		}

		/*------------------------------------------------------------
			制御文字チェック
			RPGツクール風書式で判定		例 : \\c[0]
		------------------------------------------------------------*/
		// テキストカラー変更
		if (codepoint == L'\\' && (i + 1) < mText.length() && mText[i + 1] == L'c')
		{
			if ((i + 4) < mText.length() && mText[i + 2] == L'[')
			{
				if (mText[i + 4] == L']')
				{
					// 文字から数値への簡易変換
					int colorId = mText[i + 3] - L'0';

					// テキスト色変換
					textColor = Color::ConvertColor(colorId);

					i += 4;
					continue;
				}
			}
		}

		// 最大文字数到達時の自動改行
		if (mCharsPerLine > 0 && charCount >= mCharsPerLine) {
			currentX = startX;
			currentY += _mFont->Size + _mFont->Size / 4;
			charCount = 0;
		}

		// 改行記号による手動改行
		if (codepoint == L'\n') {
			currentX = startX;
			currentY += _mFont->Size + _mFont->Size / 4;
			charCount = 0;
			continue;
		}

		// フォントリソース取得
		Glyph* glyph = FontManager::getInstance().GetGlyph(_mFont, codepoint);
		if (!glyph) {
			continue;
		}

		// 文字ごとのタイポグラフィ計算
		float finalX = currentX + static_cast<float>(glyph->BearingX);
		float finalY = currentY + static_cast<float>(glyph->BearingY);
		
		// PositionとScale更新
		transform.SetPosition(Vector3{ finalX, finalY, 0.0f });
		transform.SetScale(Vector3{ static_cast<float>(glyph->Texture->GetWidth()),
			static_cast<float>(glyph->Texture->GetHeight()), 1.0f });

		// ワールド行列セット
		D3D11::BufferManager::getInstance().SetWorldMatrix(transform.GetWorldMatrix());

		shadowDraw(glyph, transform);

		// マテリアル設定
		Element::MATERIAL material{};
		material.Diffuse = textColor;
		material.TextureEnable = true;
		D3D11::BufferManager::getInstance().SetMaterial(material);

		mCanvas.Bind();

		glyph->Texture->Bind();
		
		// 描画
		mCanvas.Draw();

		// 次の文字を参照
		currentX += glyph->Advance;
		charCount++;
	}

	// 深度ステート有効
	D3D11::DeviceManager::getInstance().SetDepthStencilState(D3D11::RenderState::Depth::Enable);

	Renderer::End();
}

void TextRenderer::shadowDraw(const Glyph* glyph, const Transform& transform) const
{
	// シャドウ用マテリアル設定
	Element::MATERIAL shadowMaterial{};
	shadowMaterial.Diffuse = XMFLOAT4{ 0.0f, 0.0f, 0.0f, 1.0f };
	shadowMaterial.TextureEnable = true;
	D3D11::BufferManager::getInstance().SetMaterial(shadowMaterial);

	// シャドウ用ワールド行列生成
	DirectX::XMMATRIX shadowOffset = DirectX::XMMatrixTranslation(0.0f, 3.0f, 0.0f);
	DirectX::XMMATRIX shadowWorld = DirectX::XMMatrixMultiply(transform.GetWorldMatrix(), shadowOffset);

	// ワールド行列をセット
	D3D11::BufferManager::getInstance().SetWorldMatrix(shadowWorld);

	// 描画
	mCanvas.Bind();
	glyph->Texture->Bind();
	mCanvas.Draw();

	// ワールド行列を元の位置に戻す
	D3D11::BufferManager::getInstance().SetWorldMatrix(transform.GetWorldMatrix());
}

TextRenderer* TextRenderer::SetFont(const std::string& fontName)
{
	_mFont = FontManager::getInstance().GetFont(fontName);
	return this;
}

TextRenderer* TextRenderer::SetTextSize(const float& size)
{
	_mFont->Size = size;
	return this;
}

TextRenderer* TextRenderer::SetText(const std::string& text)
{
	mText = Utility::String::toWideString(text);
	return this;
}

TextRenderer* TextRenderer::SetCharsPerLine(const size_t& charsPerLine)
{
	mCharsPerLine = charsPerLine;
	return this;
}
