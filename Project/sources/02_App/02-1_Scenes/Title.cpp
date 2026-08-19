/*============================================================
*	@file	 : title.cpp
*	@brief	 : タイトルシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/29
*	@updated : 2026/06/23
*============================================================*/
#include "Title.h"
#include "SceneManager.h"
#include "Game.h"
#include "Input.h"
#include <math.h>

void Title::Initialize()
{
	_mGameObjects.clear();

	//AddGameObject<Polygon2D>()->Initialize({ 0.0f, 0.0f }, { 1280.0f, 720.0f }, L"assets\\textures\\title.png");
}

void Title::Finalize()
{
	_mTexture = nullptr;
	Scene::Finalize();
}

void Title::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetKeyTrigger(VK_RETURN)) {
		SceneManager::getInstance().SceneChange<Game>();
	}
}

void Title::Draw() const
{
	Scene::Draw();
}