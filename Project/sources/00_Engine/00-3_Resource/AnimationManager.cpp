/*============================================================
*	@file	 : AnimationManager.cpp
*	@brief	 : アニメーションクリップ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "AnimationManager.h"
#include "Animation.h"

Animation* AnimationManager::Get(const std::string& keyName)
{
	auto it = mAnimations.find(keyName);

	if (it != mAnimations.end()) {
		return it->second.get();
	}

	return nullptr;
}

Animation* AnimationManager::Register(const std::string& keyName, std::unique_ptr<Animation> animation)
{
	// 登録済みならreturn
	if (mAnimations.contains(keyName)) {
		return mAnimations[keyName].get();
	}

	mAnimations.emplace(keyName, std::move(animation));

	return mAnimations[keyName].get();
}

void AnimationManager::Clear()
{
	mAnimations.clear();
}