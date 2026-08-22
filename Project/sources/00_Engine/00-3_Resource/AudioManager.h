/*============================================================
*	@file	 : AudioManager.h
*	@brief	 : オーディオ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/09
*	@updated : 2026/08/09
*============================================================*/
#pragma once

#include <string>
#include <memory>
#include <unordered_map>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Audio;

/*============================================================
*	@class	: AudioManager
*	@brief	: オーディオのロード・管理
*============================================================*/
class AudioManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static AudioManager& getInstance() {
		static AudioManager  instance;
		return instance;
	}

private:
	AudioManager() = default;
	AudioManager(const AudioManager&) = delete;

	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;

	AudioManager& operator=(AudioManager&&) = delete;
	~AudioManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
	// オーディオ形式
	enum class AudioType : char
	{
		WAV,
		MP3,
		OGG
	};

private:
	// オーディオコンテナ
	std::unordered_map <std::string, std::unique_ptr<Audio>> mAudios{};

public:
	// ロード
	Audio* Load(const char* audioPath);

	// クリア
	void Clear();

private:
	// オーディオ生成
	bool generateAudio(Audio& audio, const std::string& path);
	AudioType getType(const std::string& ext);

	bool loadWav(Audio& audio, const std::string& path);
	bool loadMp3(Audio& audio, const std::string& path);
	bool loadOgg(Audio& audio, const std::string& path);
};