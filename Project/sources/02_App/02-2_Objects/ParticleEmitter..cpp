/*============================================================
*	@file	 : ParticleEmitter.cpp
*	@brief	 : パーティクルエミッタ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/06/18
*============================================================*/
#include "ParticleEmitter.h"
#include "ParticleRenderer.h"
#include "MeshTypes.h"
#include "Input.h"

using namespace MeshType;
using namespace DirectX;

void ParticleEmitter::Initialize()
{
	ParticleRenderer* renderer = AddComponent<ParticleRenderer>(this)->SetEmitter(this);

	renderer->LoadTexture("assets\\textures\\particle.png")->LoadShader("Unlit")
		->SetBlendState(Blend::Add)->SetLayer(Layer::Alpha);

	// 構造体初期化
	mParticles.resize(PARTICLE_MAX);
	for (int i = 0; i < PARTICLE_MAX; i++) {
		mParticles[i].mEnable = false;
	}

	_mType = std::make_unique<ParticleType::Bezier>(this);

	mCount = 100;
}

void ParticleEmitter::Finalize()
{
	GameObject::Finalize();
}

void ParticleEmitter::Update(double deltaTime)
{
	_mType->Update(deltaTime);

	mCurrentInterval -= deltaTime;

	// パーティクル発射
	//if (Input::GetKeyTrigger(VK_SPACE)) {
	//	_mType->Emission();
	//}

	if (mCurrentInterval <= 0.0) {
		_mType->Emission();
		mCurrentInterval = mMaxInterval;
	}
}

void ParticleEmitter::Draw() const
{
	GameObject::Draw();
}