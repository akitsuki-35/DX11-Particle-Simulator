/*============================================================
*	@file	 : ParticleBase.cpp
*	@brief	 : パーティクル基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/19
*	@updated : 2026/08/27
*============================================================*/
#include "ParticleBase.h"
#include "ParticleBox.h"
#include "ParticleBezier.h"
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

std::unique_ptr<ParticleType::Base> ParticleType::Base::LoadCSV(const char* filePath)
{
	CSVHandler::Data data{};

	// ロード失敗時はreturn
	if (!CSVHandler::Load(filePath, data)) {
		return nullptr;
	}

	std::unique_ptr<ParticleType::Base> newType = nullptr;

	for (const auto& row : data){
		std::string tag = CSVHandler::GetString(row, 0);

		if (tag == "TYPE") {
			std::string type = CSVHandler::GetString(row, 1);
			if (type == "Box") {
				newType = std::make_unique<ParticleType::Box>(_mEmitter);
			}
			if (type == "Bezier") {
				newType = std::make_unique<ParticleType::Bezier>(_mEmitter);
			}
		}
		if (tag == "VELOCITY") {
			// 散布方向取得
			Vector3 velocity{};

			velocity.x = CSVHandler::GetFloat(row, 1, 0.0f);
			velocity.y = CSVHandler::GetFloat(row, 2, 0.0f);
			velocity.z = CSVHandler::GetFloat(row, 3, 0.0f);

			_mEmitter->SetVelocity(velocity);
		}
		if (tag == "SPREADRATE") {
			// 散布率取得
			Vector3 spreadRate{};

			spreadRate.x = CSVHandler::GetFloat(row, 1, 20.0f);
			spreadRate.y = CSVHandler::GetFloat(row, 2, 20.0f);
			spreadRate.z = CSVHandler::GetFloat(row, 3, 20.0f);

			_mEmitter->SetSpreadRate(spreadRate);
		}
		if (tag == "ACCEL") {
			// 散布率取得
			Vector3 accel{};

			accel.x = CSVHandler::GetFloat(row, 1, 0.0f);
			accel.y = CSVHandler::GetFloat(row, 2, 0.0f);
			accel.z = CSVHandler::GetFloat(row, 3, 0.0f);
			
			_mEmitter->SetAccel(accel);
		}
		if (tag == "SCALE") {
			// スケール倍率取得
			float scale = CSVHandler::GetFloat(row, 1, 1.0f);
			_mEmitter->SetScale(scale);
		}
		if (tag == "GRAVITY") {
			// 重力取得
			float gravity = CSVHandler::GetFloat(row, 1, 9.8f);
			_mEmitter->SetGravity(gravity);
		}
		if (tag == "DRAG") {
			// 重力取得
			float drag = CSVHandler::GetFloat(row, 1, -1.0f);
			_mEmitter->SetDrag(drag);
		}
		if (tag == "LIFE") {
			// 全体フレーム取得
			int life = CSVHandler::GetInt(row, 1, 60);
			_mEmitter->SetLife(life);
		}
		else if (tag == "COUNT") {
			// 発射数取得
			int count = CSVHandler::GetInt(row, 1, 100);
			_mEmitter->SetCount(count);
		}
		else if (tag == "INTERVAL") {
			// インターバル取得
			double interval = CSVHandler::GetDouble(row, 1, 0.1);
			_mEmitter->SetInterval(interval);
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

	return newType;
}