/*============================================================
*	@file	 : ParticleTypes.cpp
*	@brief	 : パーティクルタイプ定義
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/19
*============================================================*/
#include "ParticleTypes.h"
#include "ParticleEmitter.h"

void ParticleType::Base::Update(double deltaTime)
{

}

void ParticleType::Box::Emission()
{
	int count = _mEmitter->GetCount();
	auto& particles = _mEmitter->GetParticles();

	// パーティクル発射
	for (int i = 0; i < _mEmitter->GetParticleMax(); i++) {
		if (!particles[i].IsEnable()) {

			Vector3 position = _mEmitter->GetTransform().GetPosition();
			Vector3 velocity = { ((float)rand() / RAND_MAX - 0.5f) * 20.0f,
				((float)rand() / RAND_MAX) * 20.0f,
				((float)rand() / RAND_MAX - 0.5f) * 20.0f };
			float scale = ((float)rand() / RAND_MAX - 0.5f) * 5.0f;

			particles[i].Initialize(position, velocity, { scale, scale, scale });
			particles[i].Enable();

			count--;
			if (count <= 0) {
				break;
			}
		}
	}
}