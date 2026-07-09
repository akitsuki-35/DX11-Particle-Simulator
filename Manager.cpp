/*============================================================
*	@file	 : Manager.cpp
*	@brief	 : マネージャー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/21
*	@updated : 2026/06/16
*============================================================*/
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Game.h"
#include "Scene.h"
#include "Debugger.h"

Scene* Manager::mCurrentScene{ nullptr };
Scene* Manager::mNextScene{ nullptr };

/*------------------------------------------------------------
	初期化
------------------------------------------------------------*/
void Manager::Initialize()
{
	Renderer::Initialize();
	Input::Initialize();

	SceneChange<Game>();
	mCurrentScene = mNextScene;
    mNextScene = nullptr;
    mCurrentScene->Initialize();
}

/*------------------------------------------------------------
	終了
------------------------------------------------------------*/
void Manager::Finalize()
{
	mCurrentScene->Finalize();
	if (mNextScene) {
		if (mCurrentScene) {
			delete mCurrentScene;
		}
		mCurrentScene = mNextScene;
		mNextScene = nullptr;
	}

	Input::Finalize();
	Renderer::Finalize();
}

/*------------------------------------------------------------
	更新
------------------------------------------------------------*/
void Manager::Update()
{
	Input::Update();

	if(mCurrentScene) mCurrentScene->Update(1.0/60.0);

#if defined(DEBUG) || defined(_DEBUG)
	Debugger::GetInstance().Update();
#endif // defined(DEBUG) || defined(_DEBUG)

	if (mNextScene != nullptr) {
		if (mCurrentScene) {
			mCurrentScene->Finalize();
			delete mCurrentScene;
		}

		mCurrentScene = mNextScene;
		mNextScene = nullptr;
		mCurrentScene->Initialize();
	}
}

/*------------------------------------------------------------
	描画
------------------------------------------------------------*/
void Manager::Draw()
{
	Renderer::Begin();

	if(mCurrentScene) mCurrentScene->Draw();

#if defined(DEBUG) || defined(_DEBUG)
	Debugger::GetInstance().Draw();
#endif // defined(DEBUG) || defined(_DEBUG)

	Renderer::End();
}