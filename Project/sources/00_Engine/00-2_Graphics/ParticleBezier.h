/*============================================================
*	@file	 : ParticleBezier.h
*	@brief	 : ベジエ曲線上を移動するパーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/28
*	@updated : 2026/08/28
*============================================================*/
#pragma once

#include "ParticleBase.h"
#include "BezierCurve.h"

namespace ParticleType {
/*============================================================
*	@class	: Particle::Bezier
*	@brief	: ベジエ曲線上を移動するパーティクル
*============================================================*/
	class Bezier : public Base
	{
	private:
		BezierCurve mBezier{};

	public:
		Bezier(ParticleEmitter* emitter)
			: Base(emitter) {}

		void Update(double deltaTime) override;

		void Emission(ParticleDesc& desc) override;

		BezierCurve& GetBezier() { return mBezier; }

		std::unique_ptr<ParticleType::Base> LoadCSV(const char* filePath) override;
		std::string_view GetTypeName() const override { return "Bezier"; };
	};

}