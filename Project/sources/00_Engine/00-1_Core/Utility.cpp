/*============================================================
*	@file	 : Utility.cpp
*	@brief	 : 汎用ユーティリティ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/08/04
*============================================================*/
#include "Utility.h"
#include <fstream>
#include <cassert>
#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

std::vector<char> Utility::File::load(const char* filePath)
{
	// ファイルロード

	std::ifstream file(filePath, std::ios::binary);

	assert(file.is_open());

	// ファイルサイズ取得
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(static_cast<size_t>(size));

	file.read(buffer.data(), size);

	return buffer;
}

std::string Utility::File::normalizePath(const char* filePath)
{
	// ファイルパス正規化

	char fullPath[MAX_PATH];

	// 絶対パス変換
	if (!GetFullPathNameA(filePath, MAX_PATH, fullPath, nullptr)) {
		return std::string(filePath);
	}

	char canonical[MAX_PATH];

	// 正規化
	if (PathCanonicalizeA(canonical, fullPath)) {
		return std::string(canonical);
	}

	// 正規化失敗時は絶対パスを返す
	return std::string(fullPath);
}

std::filesystem::path Utility::File::getDirectoryPath(const char* filePath)
{
	// ディレクトリのパス取得
	std::filesystem::path directory = filePath;
	directory = directory.parent_path();
	
	// 文字列連結によるパス組み立て用
	directory += "\\";

	return directory;
}

std::string Utility::File::getFileExtension(const std::string& filePath)
{
	// ファイル拡張子取得
	auto pos = filePath.find_last_of('.');

	std::string ext = filePath.substr(pos + 1);
	
	for (auto& c : ext) {
		c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
	}

	return ext;
}

std::wstring Utility::String::toWideString(const std::string& string)
{
	// std::string→std::wstringに変換

	if (string.empty())
	{
		return{};
	}

	// 終端文字を含む文字列を取得
	const int size = MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, nullptr, 0);

	assert(size > 0);

	std::wstring wide(size - 1, L'\0');

	MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, wide.data(), size);

	return wide;
}
