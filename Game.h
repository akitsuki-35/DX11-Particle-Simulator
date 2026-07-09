/*============================================================
*	@file	 : Game.h
*	@brief	 : ゲームシーン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/03/28
*	@updated : 2026/06/23
*============================================================*/
#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "GameObject.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class GameObject;

/*============================================================
*	@class	: Game
*	@brief	: ゲームシーン（Sceneを継承）
*============================================================*/
class Game : public Scene
{
private:
	static std::list<GameObject*> gameObjects;

public:
	void Initialize() override;
	void Finalize() override;
	void Update(double elapsedTime) override;
	void Draw() const override;

	template <typename T> // テンプレート関数
	static T* AddGameObject() {
		T* gameObject = new T();
		gameObject->Initialize();
		gameObjects.push_back(gameObject);

		return gameObject;
	}

	template <typename T> // テンプレート関数
	static T* GetGameObject() {
		for (GameObject* gameObject : gameObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(gameObject);
			if (find) return find;
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (GameObject* gameObject : gameObjects) {
			// RTTI（実行時型情報）
			T* find = dynamic_cast<T*>(gameObject);
			if (find != nullptr) {
				objects.push_back(find);
			}
		}
		return objects;
	}
};

#endif // GAME_H
