/*============================================================
*	@file	 : CSVHandler.h
*	@brief	 : CSVファイル読み込み・書き出し
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/21
*	@updated : 2026/08/21
*============================================================*/
#pragma once

#include <string>
#include <vector>

/*============================================================
*	@class	: CSVHandler
*	@brief	: CSVファイル読み込み・書き出し
*============================================================*/
class CSVHandler final
{
private:
	CSVHandler() = delete;

public:
	using Row = std::vector<std::string>;
	using Data = std::vector<Row>;

	static bool Load(const char* filePath, Data& data);
	static bool Export(const char* filePath, const Data& data);

	static std::string GetString(const Row& row, size_t index, const std::string& defaultValue = "");
	static int GetInt(const Row& row, size_t index, int defaultValue = 0);
	static float GetFloat(const Row& row, size_t index, float defaultValue = 0.0f);
	static double GetDouble(const Row& row, size_t index, double defaultValue = 0.0);

private:
	static std::string trim(const std::string& str);
};