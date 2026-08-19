/*============================================================
*	@file	 : Scene.h
*	@brief	 : シーン基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2025/09/17
*	@updated : 2026/08/15
*============================================================*/
#pragma once

#include "GameObject.h"
#include <list>
#include <vector>
#include <memory>

/*============================================================
*	@class	: Scene
*	@brief	: シーン基底クラス
*============================================================*/
class Scene
{
protected:
	inline static std::list<std::unique_ptr<GameObject>> _mGameObjects;

public:
	virtual ~Scene() = default;

	virtual void Initialize() = 0;
	virtual void Finalize();
	virtual void Update(double deltaTime);
	virtual void Draw() const;

	template <typename T>
	static T* AddGameObject() {
		auto gameObject = std::make_unique<T>();
		gameObject->Initialize();
		T* ptr = gameObject.get();
		_mGameObjects.push_back(std::move(gameObject));

		return ptr;
	}

	template <typename T>
	static T* GetGameObject() {
		for (const auto& gameObject : _mGameObjects) {
			T* find = dynamic_cast<T*>(gameObject.get());
			if (find) return find;
		}
		return nullptr;
	}

	template <typename T>
	static std::vector<T*> GetGameObjects() {
		std::vector<T*> objects;
		for (const auto& gameObject : _mGameObjects) {
			T* find = dynamic_cast<T*>(gameObject.get());
			if (find != nullptr) {
				objects.push_back(find);
			}
		}
		return objects;
	}
};