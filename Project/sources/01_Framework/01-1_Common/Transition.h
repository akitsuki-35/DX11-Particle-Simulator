/*============================================================
*	@file	 : Transition.h
*	@brief	 : フェード制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "UIRenderer.h"
#include "Transform.h"
#include "Config.h"
#include <DirectXMath.h>
#include <memory>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class UIRenderer;

/*============================================================
*	@class	: Transition
*	@brief	: フェード制御
*============================================================*/
class Transition
{
public:
	// フェードの推移状態
	enum class State : int
	{
		None,
		FadeOut,
		FadeOutEnd,
		FadeIn,
		FadeInEnd
	};

/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static Transition& getInstance() {
		static Transition instance;
		return instance;
	}

private:
	Transition() = default;
	Transition(const Transition&) = delete;

	Transition& operator=(const Transition&) = delete;
	Transition(Transition&&) = delete;

	Transition& operator=(Transition&&) = delete;
	~Transition() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	State mState{};
	double mTime{ 60.0f }; // トランジション総時間
	double mAccumulatedtime{}; // 総経過時間
	double mStartTime{}; // トランジション開始時間

	std::unique_ptr<UIRenderer> _mRenderer{}; // レンダラー
	Transform mTransform{}; // トランスフォーム

public:
	void Initialize();
	void Finalize();
	void Update(double deltaTime);
	void Draw() const;

	// フェード開始
	void Start(const double& fadeTime, const bool& isFadeIn,
		const Color::Index& color = Color::Index::Black);
	Transition::State GetState() const { return mState; }
};