/*============================================================
*	@file	 : ParticleBox.h
*	@brief	 : ボックス型散布パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/27
*	@updated : 2026/08/27
*============================================================*/
#pragma once

#include "ParticleBase.h"

namespace ParticleType {
/*============================================================
*	@class	: Particle::Box
*	@brief	: ボックス型パーティクル
*============================================================*/
	class Box : public Base
	{
	public:
		Box(ParticleEmitter* emitter)
			: Base(emitter) {}

		void Emission(ParticleDesc& desc) override;

		std::string_view GetTypeName() const override { return "Box"; };
	};
}