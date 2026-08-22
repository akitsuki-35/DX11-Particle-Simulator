/*============================================================
*	@file	 : ParticleGUI.h
*	@brief	 : パーティクル制御用GUI
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/22
*	@updated : 2026/08/22
*============================================================*/
#pragma once

#include <vector>
#include <string>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class ParticleEmitter;

/*============================================================
*	@class	: ParticleGUI
*	@brief	: パーティクル制御用GUI
*============================================================*/
class ParticleGUI final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static ParticleGUI& getInstance() {
		static ParticleGUI instance;
		return instance;
	}

private:
	ParticleGUI() = default;
	ParticleGUI(const ParticleGUI&) = delete;

	ParticleGUI& operator=(const ParticleGUI&) = delete;
	ParticleGUI(ParticleGUI&&) = delete;

	ParticleGUI& operator=(ParticleGUI&&) = delete;
	~ParticleGUI() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	std::string mLog{};

	std::vector<std::string> mCSVFiles{};
	int mCSVIndex{ 0 };

	std::vector<std::string> mTextureFiles{};
	int mTextureIndex{ 0 };

public:
	const void Display();

private:
	const void parameterControl(ParticleEmitter* emitter);

	const void fileControl(ParticleEmitter* emitter);

	const void loadCSV(ParticleEmitter* emitter);
	const void CSVListInitialize();
	const bool exportCSV(ParticleEmitter* emitter, std::string fileName);

	const void loadTexture(ParticleEmitter* emitter);
	const void textureListInitialize();

	const void particleControl(ParticleEmitter* emitter);
	const void typeControl(ParticleEmitter* emitter);
	const void bezierControl(ParticleEmitter* emitter);
};