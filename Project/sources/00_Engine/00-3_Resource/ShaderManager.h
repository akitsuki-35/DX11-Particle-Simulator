/*============================================================
*	@file	 : ShaderManager.h
*	@brief	 : シェーダーリソース管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Shader.h"
#include <string>
#include <memory>
#include <unordered_map>

/*============================================================
*	@class	: ShaderManager
*	@brief	: シェーダーのロード・管理
*============================================================*/
class ShaderManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static ShaderManager& getInstance() {
		static ShaderManager  instance;
		return instance;
	}

private:
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;

	ShaderManager& operator=(const ShaderManager&) = delete;
	ShaderManager(ShaderManager&&) = delete;

	ShaderManager& operator=(ShaderManager&&) = delete;
	~ShaderManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	// シェーダーコンテナ
	std::unordered_map<std::string, std::unique_ptr<Shader>> mShaders{};

	// キャッシュ
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11VertexShader>> mVSCache{};
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11PixelShader>> mPSCache{};
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11InputLayout>>  mLayoutCache{};

public:
	// 登録済みシェーダーの取得
	Shader* Get(const std::string& keyName);

	// 登録
	Shader* Register(const std::string& keyName,
		const char* vsPath, const char* psPath);

	// クリア
	void Clear();
};

namespace ShaderSet {
	inline void initialize() {
		ShaderManager::getInstance().Register("UI",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\UnlitPS.cso");

		ShaderManager::getInstance().Register("Font",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\FontPS.cso");

		ShaderManager::getInstance().Register("FontOutline",
			"assets\\shaders\\UISpriteVS.cso", "assets\\shaders\\FontOutlinePS.cso");

		ShaderManager::getInstance().Register("Unlit",
			"assets\\shaders\\UnlitVS.cso", "assets\\shaders\\UnlitPS.cso");

		ShaderManager::getInstance().Register("Directional",
			"assets\\shaders\\DirectionalVS.cso", "assets\\shaders\\DirectionalPS.cso");
	}
}