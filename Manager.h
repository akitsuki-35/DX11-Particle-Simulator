/*============================================================
*	@file	 : Manager.h
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/02
*============================================================*/
#ifndef MANAGER_H
#define MANAGER_H

#include "Main.h"
#include "GameObject.h"
#include "Scene.h"

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Scene;

/*============================================================
*	@class	: Manager
*	@brief	: ゲーム全体の処理を管理するマネージャークラス
*============================================================*/
class Manager
{
private:
	static Scene* mCurrentScene;
	static Scene* mNextScene;

public:
	static void Initialize();
	static void Finalize();
	static void Update();
	static void Draw();

	template <class T>
	static void SceneChange() {
		mNextScene = new T();
	}
};

#endif // MANAGER_H