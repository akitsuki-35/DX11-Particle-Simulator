/*============================================================
*	@file	 : Result.cpp
*	@brief	 : リザルトシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/08/15
*============================================================*/
#include "Result.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"
#include <math.h>

void Result::Initialize()
{
	_mGameObjects.clear();

	//AddResultObject<Polygon2D>()->Initialize({ 0.0f, 0.0f }, { 1280.0f, 720.0f }, L"Resources\\Textures\\Result.png");
}

void Result::Finalize()
{
	_mTexture = nullptr;
	Scene::Finalize();
}

void Result::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetKeyTrigger(VK_RETURN)) {
		SceneManager::getInstance().SceneChange<Title>();
	}
}

void Result::Draw() const
{
	Scene::Draw();
}