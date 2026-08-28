/*============================================================
*	@file	 : Game.cpp
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/08/04
*============================================================*/
#include "Game.h"
#include "SceneManager.h"
#include "Input.h"
#include "Camera.h"
#include "Transition.h"

#include "Field.h"
#include "Sky.h"

#include "ParticleEmitter.h"
#include "Grid.h"

#include "DeviceManager.h"
#include "D3D11Config.h"

void Game::Initialize()
{
	//Transition::getInstance().Start(1.0, true);

	_mGameObjects.clear();

	AddGameObject<Camera>();
	AddGameObject<Grid>()->SetPosition({ 0.0f, 0.0f, 0.0f });

	//AddGameObject<Sky>();

	AddGameObject<ParticleEmitter>()->LoadCSV("assets\\csv\\test.csv")->SetPosition({ 0.0f, 0.0f, 0.0f });
}

void Game::Finalize()
{
	Scene::Finalize();
}

void Game::Update(double deltaTime)
{
	Scene::Update(deltaTime);
}

void Game::Draw() const
{
	Scene::Draw();
}