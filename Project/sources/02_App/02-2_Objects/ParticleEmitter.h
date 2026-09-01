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
#include "ParticleBase.h"
#include <memory>

// パーティクル本体の初期化に使用するデータ構造体
struct ParticleDesc {
	Vector3 Velocity{ 0.0f, 10.0f, 0.0f }; // 散布方向
	Vector3 SpreadRate{ 20.0f, 20.0f, 20.0f }; // 散布率
	Vector3 Accel{}; // 加速度
	float Scale{ 5.0f }; // スケール倍率
	float Gravity{ 9.8f }; // 重力
	float Drag{ -1.0f }; // 抵抗
	int Life{ 60 }; // 全体フレーム
};

/*============================================================
*	@class	: ParticleEmitter
*	@brief	: パーティクルエミッタ
*============================================================*/
class ParticleEmitter : public GameObject
{
	friend class ParticleRenderer;
	friend class ParticleGUI;

private:
	static constexpr int PARTICLE_MAX{ 10000 };
	std::vector<Particle> mParticles{};

	// データ構造体
	ParticleDesc mDesc{};

	// 発射インターバル
	double mMaxInterval{ 0.1 };
	double mCurrentInterval{};

	// 一度あたりの発射数
	int mCount{ 100 };

	// パーティクルタイプ
	std::unique_ptr<ParticleType::Base> _mType{};

public:	
	ParticleEmitter() = default;

	void Initialize() override;
	void Finalize() override;
	void Update(double deltaTime) override;
	void Draw() const override;

	// ゲッター
	ParticleType::Base* GetType() const { return _mType.get(); }
	int GetParticleMax() const { return PARTICLE_MAX; }
	std::vector<Particle>& GetParticles() { return mParticles; }
	int GetCount() const { return mCount; }
	ParticleDesc GetDesc() const { return mDesc; }
	int GetLife() const { return  mDesc.Life; }

	// セッター
	void SetVelocity(const Vector3& velocity) { mDesc.Velocity = velocity; }
	void SetSpreadRate(const Vector3& spreadRate) { mDesc.SpreadRate = spreadRate; }
	void SetAccel(const Vector3& accel) { mDesc.Accel = accel; }
	void SetScale(const float& scale) { mDesc.Scale = scale; }
	void SetGravity(const float& gravity) { mDesc.Gravity = gravity; }
	void SetDrag(const float& drag) { mDesc.Drag = drag; }
	void SetLife(const int& life) { mDesc.Life = life; }
	void SetCount(const int& count) { mCount = count; }
	void SetInterval(const double& interval) { mMaxInterval = mCurrentInterval = interval; }
	void SetType(std::unique_ptr<ParticleType::Base> type) { _mType = std::move(type); }

	// CSVファイル読み込み
	ParticleEmitter* LoadCSV(const char* filePath);
};