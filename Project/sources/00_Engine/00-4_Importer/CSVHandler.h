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
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static CSVHandler& getInstance() {
		static CSVHandler instance;
		return instance;
	}

private:
	CSVHandler() = default;
	CSVHandler(const CSVHandler&) = delete;

	CSVHandler& operator=(const CSVHandler&) = delete;
	CSVHandler(CSVHandler&&) = delete;

	CSVHandler& operator=(CSVHandler&&) = delete;
	~CSVHandler() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
public:
	using Row = std::vector<std::string>;
	using Data = std::vector<Row>;

	bool Load(const char* filePath, Data& data);
	static bool Export(const char* filePath, const Data& data);

	std::string GetString(const Row& row, size_t index, const std::string& defaultValue = "");
	float GetFloat(const Row& row, size_t index, float defaultValue = 0.0f);
	int GetInt(const Row& row, size_t index, int defaultValue = 0);

private:
	std::string trim(const std::string& str);
};