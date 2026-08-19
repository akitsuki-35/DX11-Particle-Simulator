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
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Tree.h"
#include "Sky.h"
#include "Box.h"
#include "Shadow.h"

#include "ParticleEmitter.h"
#include "Result.h"

#include "Score.h"

#include "DeviceManager.h"
#include "D3D11Config.h"

void Game::Initialize()
{
	Transition::getInstance().Start(1.0, true);

	_mGameObjects.clear();

	AddGameObject<Camera>();

	AddGameObject<Sky>();

	AddGameObject<Field>();
	AddGameObject<Player>();
	AddGameObject<Enemy>()->SetPosition({ 5.0f, 0.0f, 5.0f });
	AddGameObject<Enemy>()->SetPosition({ -5.0f, 0.0f, 5.0f });
	AddGameObject<Enemy>()->SetPosition({ 0.0f, 0.0f, 5.0f });
	Box* box = AddGameObject<Box>();
	box->SetPosition({ 0.0f, 0.0f, -5.0f });
	box->SetScale({ 1.0f, 1.0f, 1.0f });

	AddGameObject<Tree>()->SetPosition({ -5.0f,0.0f, 5.0f });
	AddGameObject<Tree>()->SetPosition({ -5.0f,0.0f, 0.0f });

	AddGameObject<Shadow>()->SetPosition({ 0.0f, 0.1f, 0.0f });

	AddGameObject<ParticleEmitter>()->SetPosition({ 0.0f, 0.0f, 0.0f });

	AddGameObject<Score>();
}

void Game::Finalize()
{
	Scene::Finalize();
}

void Game::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	if (Input::GetKeyTrigger(VK_RETURN)) {
		SceneManager::getInstance().SceneChange<Result>();
	}
}

void Game::Draw() const
{
	Scene::Draw();
}