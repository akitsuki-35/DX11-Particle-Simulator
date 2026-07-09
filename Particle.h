/*============================================================
*	@file	 : particle.h
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/06/18
*============================================================*/
#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"
#include "Debugger.h"

class BezierCurve;

/*============================================================
*	@class	: Particle
*	@brief	: パーティクルシステム
*============================================================*/
class Particle : public GameObject
{
private:
	// パーティクル構造体
	struct PARTICLE
	{
		Vector3 position;
		Vector3 velocity;
		Vector3 accel;
		Vector3 scale{ 1.0f, 1.0f, 1.0f };
		int life;
		bool enable;
	};

	GameObject* mObject{ nullptr };

	static constexpr int PARTICLE_MAX{ 10000 };
	PARTICLE mParticle[PARTICLE_MAX]{};
	XMFLOAT4 mMainColor{ 1.0f, 0.2f, 0.2f, 1.0f };
	XMFLOAT4 mSubColor{ 0.2f, 0.2f, 1.0f, 1.0f };

	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	Particle() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	void SetObject(GameObject* obj) { mObject = obj; }
	void SetMainColor(const XMFLOAT4& color) { mMainColor = color; }
	void SetSubColor(const XMFLOAT4& color) { mSubColor = color; }
};

/*============================================================
*	@class	: ParticleBezier
*	@brief	: ベジエ曲線上を移動するパーティクル
*============================================================*/
class ParticleBezier : public GameObject
{
	friend Debugger;
private:
	// パーティクル構造体
	struct PARTICLE
	{
		Vector3 position;
		Vector3 velocity;
		Vector3 accel;
		Vector3 scale{ 1.0f, 1.0f, 1.0f };
		int life;
		bool enable;
		int t; // 時間
	};

	BezierCurve* _mBezier{ nullptr }; // ベジエ曲線
	double mInterval{}; // 発射間隔

	// ImGuiデバッガーから変更可能な値として定義
	int Life{ 60 }; // パーティクル寿命
	double Interval{ 0.1 }; // 発射間隔
	int Count{ 100 }; // 一度の発射数

	static constexpr int PARTICLE_MAX{ 10000 };
	PARTICLE mParticle[PARTICLE_MAX]{};
	XMFLOAT4 mMainColor{ 1.0f, 0.2f, 0.2f, 1.0f };
	XMFLOAT4 mSubColor{ 0.2f, 0.2f, 1.0f, 1.0f };

	ID3D11Buffer* _mVertexBuffer{}; // 頂点バッファ
	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

	ID3D11ShaderResourceView* _mTexture{}; // テクスチャ

public:
	ParticleBezier() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	void SetMainColor(const XMFLOAT4& color) { mMainColor = color; }
	void SetSubColor(const XMFLOAT4& color) { mSubColor = color; }
	BezierCurve* GetBezier() { return _mBezier; }
};

#endif // PARTICLE_H