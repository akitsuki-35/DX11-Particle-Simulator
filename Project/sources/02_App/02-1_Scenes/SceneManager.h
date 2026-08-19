/*============================================================
*	@file	 : SceneManager.h
*	@brief	 : シーン管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Scene.h"
#include <memory>

/*============================================================
*	@class	: SceneManager
*	@brief	: シーン管理
*============================================================*/
class SceneManager final
{
/*--------------------------------------------------
	Singleton用
----------------------------------------------------*/
public:
	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}

private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;

	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;

	SceneManager& operator=(SceneManager&&) = delete;
	~SceneManager() {};

/*--------------------------------------------------
	メンバ変数・メンバ関数
----------------------------------------------------*/
private:
	std::unique_ptr<Scene> mCurrentScene{};
	std::unique_ptr<Scene> mNextScene{};

public:
	void Initialize();
	void Finalize();
	void Update(double deltaTime);
	void Draw();

	template <class T>
	void SceneChange() {
		mNextScene = std::make_unique<T>();
	}
};