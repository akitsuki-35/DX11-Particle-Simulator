/*============================================================
*	@file	 : ParticleBase.cpp
*	@brief	 : パーティクル基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/27
*============================================================*/
#include "ParticleBase.h"
#include "ParticleEmitter.h"
#include "ParticleRenderer.h"
#include "CSVHandler.h"

using namespace DirectX;

void ParticleType::Base::Update(double deltaTime)
{
	auto& particles = _mEmitter->GetParticles();
	for (int i = 0; i < _mEmitter->GetParticleMax(); i++) {
		particles[i].Update(deltaTime);
	}
}

ParticleType::Base* ParticleType::Base::LoadCSV(const char* filePath)
{
	CSVHandler::Data data{};

	// ロード失敗時はreturn
	if (!CSVHandler::Load(filePath, data)) {
		return this;
	}

	for (const auto& row : data){
		std::string tag = CSVHandler::GetString(row, 0);
		std::string type{};

		if (tag == "TYPE") {
			type = CSVHandler::GetString(row, 1);
		}
		if (tag == "LIFE") {
			// 全体フレーム取得
			int life = CSVHandler::GetInt(row, 1, 60);
			_mEmitter->SetLife(life);
		}
		else if (tag == "INTERVAL") {
			// インターバル取得
			double interval = CSVHandler::GetDouble(row, 1, 0.1);
			_mEmitter->SetInterval(interval);
		}
		else if (tag == "COUNT") {
			// 発射数取得
			int count = CSVHandler::GetInt(row, 1, 100);
			_mEmitter->SetCount(count);
		}
		else if (tag == "MAINCOLOR") {
			// メインカラー取得
			XMFLOAT4 color{};

			color.x = CSVHandler::GetFloat(row, 1, 1.0f);
			color.y = CSVHandler::GetFloat(row, 2, 1.0f);
			color.z = CSVHandler::GetFloat(row, 3, 1.0f);
			color.w = CSVHandler::GetFloat(row, 4, 1.0f);

			_mEmitter->GetComponent<ParticleRenderer>()->SetColor(color);
		}
		else if (tag == "SUBCOLOR") {
			// サブカラー取得
			XMFLOAT4 color{};

			color.x = CSVHandler::GetFloat(row, 1, 1.0f);
			color.y = CSVHandler::GetFloat(row, 2, 1.0f);
			color.z = CSVHandler::GetFloat(row, 3, 1.0f);
			color.w = CSVHandler::GetFloat(row, 4, 1.0f);

			_mEmitter->GetComponent<ParticleRenderer>()->SetSubColor(color);
		}
	}

	return this;
}

void ParticleType::Bezier::Update(double deltaTime)
{
	// 現フレームのベジエ曲線上の座標を取得
	mBezier.Update();
	_mEmitter->SetPosition(mBezier.GetBezierPoint(mBezier.GetFrame()));

	Base::Update(deltaTime);
}

void ParticleType::Bezier::Emission()
{
	int count = _mEmitter->GetCount();
	auto& particles = _mEmitter->GetParticles();

	// 全体フレームをセット
	mBezier.SetFrameMax(_mEmitter->GetLife());

	// ベジエ曲線再計算
	mBezier.CalcBezier();

	// 現フレームのベジエ曲線上の座標を取得
	mBezier.Update();
	_mEmitter->SetPosition(mBezier.GetBezierPoint(mBezier.GetFrame()));

	Vector3 position = _mEmitter->GetTransform().GetPosition();

	// パーティクル発射
	for (int i = 0; i < _mEmitter->GetParticleMax(); i++) {
		if (!particles[i].IsEnable()) {
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
