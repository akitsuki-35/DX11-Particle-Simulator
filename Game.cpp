/*============================================================
*	@file	 : Game.cpp
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/07/09
*============================================================*/
#include "Main.h"
#include "Game.h"
#include "Scene.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "GameObject.h"

#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Tree.h"
#include "Sky.h"
#include "Box.h"

#include "Particle.h"

std::list<GameObject*> Game::gameObjects;

void Game::Initialize()
{
	gameObjects.clear();

	AddGameObject<Camera>();

	AddGameObject<Sky>();

	AddGameObject<Player>();

	// オブジェクトを追従するパーティクル
	Particle* particle = AddGameObject<Particle>();
	particle->SetObject(GetGameObject<Player>());
	particle->SetMainColor({ 1.0f, 0.6f, 0.2f, 1.0f });
	particle->SetSubColor({ 0.2f, 1.0f, 0.3f, 1.0f });

	// ベジエ曲線上を移動するパーティクル
	ParticleBezier* particleBezier = AddGameObject<ParticleBezier>();
}

void Game::Finalize()
{
	for (GameObject* obj : gameObjects) {
		obj->Finalize();
		delete obj;
	}
}

void Game::Update(double elapsedTime)
{
	for (GameObject* obj : gameObjects) {
		obj->Update();
	}

	// ゲームオブジェクト削除
	gameObjects.remove_if([](GameObject* object) {
		return object->Destroy();
		});
}

void Game::Draw() const
{
	// Zソート
	{
		Camera* camera = GetGameObject<Camera>();

		if (camera) {

			Vector3 forward = camera->GetForward();
			Vector3 position = camera->GetPosition();

			for (GameObject* obj : gameObjects) {
				obj->CalcCameraZ(position, forward);
			}

			gameObjects.sort([](GameObject* a, GameObject* b) {
				return a->GetCameraZ() > b->GetCameraZ();
				});
		}
	}

	for (int layer = 0; layer < 4; layer++)
	{
		for (GameObject* obj : gameObjects) {
			if (obj->GetLayer() == layer) {
				obj->Draw();
			}
		}
	}
}