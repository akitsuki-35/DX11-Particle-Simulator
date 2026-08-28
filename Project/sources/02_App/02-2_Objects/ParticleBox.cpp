/*============================================================
*	@file	 : ParticleBox.h
*	@brief	 : ボックス型散布パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/27
*	@updated : 2026/08/27
*============================================================*/
#include "ParticleBox.h"
#include "ParticleEmitter.h"

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

			particles[i].SetParameter(position, velocity, { scale, scale, scale }, _mEmitter->GetLife());
			particles[i].Enable();

			count--;
			if (count <= 0) {
				break;
			}
		}
	}
}