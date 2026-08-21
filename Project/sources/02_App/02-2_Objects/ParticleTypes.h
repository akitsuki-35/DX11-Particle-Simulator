/*============================================================
*	@file	 : ParticleTypes.h
*	@brief	 : パーティクルタイプ定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/19
*============================================================*/
#pragma once

#include "BezierCurve.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class ParticleEmitter;

/*============================================================
*	@namespace	: ParticleType
*	@brief		: パーティクル形状クラス群
*============================================================*/
namespace ParticleType {
	/*============================================================
	*	@class	: Particle::Base
	*	@brief	: パーティクル形状基底クラス
	*============================================================*/
	class Type
	{
	protected:
		ParticleEmitter* _mEmitter{};

	public:
		Type(ParticleEmitter* emitter) 
			:_mEmitter(emitter) {}
		virtual ~Type() = default;

		virtual void Emission() = 0;
		virtual void Update(double deltaTime);
		virtual Type* LoadCSV(const char* filePath);
	};

	/*============================================================
	*	@class	: Particle::Box
	*	@brief	: ボックス型パーティクル
	*============================================================*/
	class Box : public Type
	{
	public:
		Box(ParticleEmitter* emitter)
			: Type(emitter) {}

		void Emission() override;
	};

	/*============================================================
	*	@class	: Particle::Bezier
	*	@brief	: ベジエ曲線上を移動するパーティクル
	*============================================================*/
	class Bezier : public Type
	{
	private:
		BezierCurve mBezier{};

	public:
		Bezier(ParticleEmitter* emitter)
			: Type(emitter) {}

		void Update(double deltaTime) override;

		void Emission() override;

		BezierCurve& GetBezier() { return mBezier; }
	};
}