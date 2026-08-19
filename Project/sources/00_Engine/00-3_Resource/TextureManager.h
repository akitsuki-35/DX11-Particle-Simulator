/*============================================================
*	@file	 : TextureManager.h
*	@brief	 : テクスチャリソース管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Texture;

/*============================================================
*	@class	: TextureManager
*	@brief	: テクスチャのロード・管理
*============================================================*/
class TextureManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static TextureManager& getInstance() {
		static TextureManager  instance;
		return instance;
	}

private:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;

	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;

	TextureManager& operator=(TextureManager&&) = delete;
	~TextureManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// テクスチャコンテナ
	std::unordered_map <std::string, std::unique_ptr<Texture>> mTextures{};

public:
	// ロード
	Texture* Load(const char* texturePath);

	// クリア
	void Clear();

private:
	// テクスチャ生成
	bool generateTexture(Texture& texture, const std::string& path);
};