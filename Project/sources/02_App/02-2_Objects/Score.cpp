/*============================================================
*	@file	 : Score.cpp
*	@brief	 : スコア表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/30
*	@updated : 2026/08/12
*============================================================*/
#include "Score.h"
#include "TextRenderer.h"
#include "FontLoader.h"

void Score::Initialize()
{
	//TextRenderer* renderer = AddComponent<TextRenderer>(this);

	//mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });

	//renderer->SetFont("LogoTypeGothic")->
	//	SetText("あの\\c[7]イーハトーヴォ\\c[0]のすきとおった風、夏でも底に冷たさをもつ青いそら、うつくしい森で飾られたモリーオ市、郊外のぎらぎらひかる草の波")
	//	->SetTextSize(48.0f)
	//	->LoadShader("FontOutline");

	UIRenderer* renderer = AddComponent<UIRenderer>(this);

	renderer->GetCanvas().CreateCanvas(UIStyle::Pivot::LeftTop);

	mTransform.SetPosition({ 0.0f, 0.0f, 0.0f });
	mTransform.SetScale({ 1000.0f, 100.0f, 0.0f });

	renderer->LoadTexture("assets\\textures\\game_ui.png")->LoadShader("UI");

	mValue = 0;
}

void Score::Finalize()
{
	GameObject::Finalize();
}

void Score::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Score::Draw() const
{
	GameObject::Draw();
}