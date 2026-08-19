/*============================================================
*	@file	 : Transition.cpp
*	@brief	 : トランジション制御
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/16
*============================================================*/
#include "Transition.h"

using namespace::DirectX;

void Transition::Initialize()
{
	_mRenderer = std::make_unique<UIRenderer>();
	_mRenderer->GetCanvas().CreateCanvas(UIStyle::Pivot::LeftTop);

	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	mTransform.SetScale({ Screen::WIDTH, Screen::HEIGHT, 0.0f });

	_mRenderer->LoadShader("UI");

	mState = State::None;
	mAccumulatedtime = 0.0;
	mTime = 0.0;
}

void Transition::Finalize()
{
	_mRenderer->Finalize();
	_mRenderer = nullptr;
}

void Transition::Update(double deltaTime)
{
	float dt = static_cast<float>(deltaTime);

	// 時間計測とステートの管理
	if (mState == State::None || mState == State::FadeOutEnd || mState == State::FadeInEnd) {
		return;
	}

	mAccumulatedtime += dt;

	double lifeTime = mAccumulatedtime;

	double progress = lifeTime / mTime;
	if (progress > 1.0) progress = 1.0;
	if (progress < 0.0) progress = 0.0;

	float alpha = static_cast<float>(progress);

	XMFLOAT4 color = _mRenderer->GetColor();
	color.w = mState == State::FadeIn ? 1.0f - alpha : alpha;
	_mRenderer->SetColor({ color });

	if (mTime <= lifeTime) {
		mState = (mState == State::FadeIn) ? State::FadeInEnd : State::FadeOutEnd;
	}
}

void Transition::Draw() const
{
	if (mState == State::None || mState == State::FadeInEnd) {
		return;
	}

	if (!_mRenderer->GetTexture()) {
		_mRenderer->LoadTexture("assets\\textures\\white.png");
	}

	_mRenderer->Draw(mTransform);
}

void Transition::Start(const double& fadeTime, const bool& isFadeIn, const Color::Index& color)
{
	mTime = fadeTime;
	mState = isFadeIn ? State::FadeIn : State::FadeOut;

	mAccumulatedtime = 0.0;

	//mStartTime = mAccumulatedtime;
	XMFLOAT4 initColor = Color::ConvertColor(static_cast<int>(color));
	initColor.w = isFadeIn ? 1.0f : 0.0f;
	_mRenderer->SetColor(initColor);
}