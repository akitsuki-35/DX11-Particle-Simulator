/*============================================================
*	@file	 : ParticleEmitter.h
*	@brief	 : パーティクルエミッタ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "GameObject.h"
#include "Particle.h"
#include "ParticleTypes.h"
#include <memory>

/*============================================================
*	@class	: ParticleEmitter
*	@brief	: パーティクルエミッタ
*============================================================*/
class ParticleEmitter : public GameObject
{
	friend class ParticleRenderer;

private:
	static constexpr int PARTICLE_MAX{ 10000 };
	std::vector<Particle> mParticles{};
	int mCount{ 100 }; // 一度あたりの発射数
	int mLife{ 60 };

	std::unique_ptr<ParticleType::Base> _mType{};

public:	
	ParticleEmitter() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// ゲッター
	int GetParticleMax() const { return PARTICLE_MAX; }
	std::vector<Particle>& GetParticles() { return mParticles; }
	int GetCount() const { return mCount; }
	int GetLife() const { return mLife; }
};