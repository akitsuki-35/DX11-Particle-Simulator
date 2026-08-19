/*============================================================
*	@file	 : ParticleTypes.h
*	@brief	 : パーティクルタイプ定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/19
*============================================================*/
#pragma once

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
	class Base
	{
	protected:
		ParticleEmitter* _mEmitter{};

	public:
		virtual ~Base() = default;

		virtual void Emission() = 0;
		virtual void Update(double deltaTime);
	};

	/*============================================================
	*	@class	: Particle::Box
	*	@brief	: ボックス型パーティクル
	*============================================================*/
	class Box : public Base
	{
	public:
		void Emission() override;
	};
}