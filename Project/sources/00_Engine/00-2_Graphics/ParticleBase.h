/*============================================================
*	@file	 : ParticleBase.h
*	@brief	 : パーティクルタイプ定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/27
*============================================================*/
#pragma once

#include <string>
#include <string_view>
#include <memory>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class ParticleEmitter;
struct ParticleDesc;

namespace ParticleType {
/*============================================================
*	@class	: Particle::Base
*	@brief	: パーティクル形状基底クラス
*============================================================*/
	class Base
	{
		friend ParticleEmitter;

	protected:
		ParticleEmitter* _mEmitter{};

	public:
		Base(ParticleEmitter* emitter) 
			:_mEmitter(emitter) {}
		virtual ~Base() = default;

		virtual void Emission(ParticleDesc& desc) = 0;
		virtual void Update(double deltaTime);

		// CSVファイル読み込み・書き出し
		virtual std::unique_ptr<ParticleType::Base> LoadCSV(const char* filePath);
		virtual std::string_view GetTypeName() const = 0;
	};
}