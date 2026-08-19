/*============================================================
*	@file	 : Animator.h
*	@brief	 : アニメーターコンポーネント
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include "Component.h"
#include "Animation.h"
#include <string>
#include <cassert>

/*------------------------------------------------------------
	前方宣言
------------------------------------------------------------*/
class Skeleton;

/*============================================================
*	@class	: Animator
*	@brief	: アニメーターコンポーネント
*============================================================*/
class Animator final : public Component
{
private:
    class Skeleton* _mSkeleton{};
    class Animation* _mAnimation{};
    double mCurrentTime{};

public:
    Animator(GameObject* owner)
        : Component(owner) {}

    void Finalize() override {
        _mSkeleton = nullptr;
        _mAnimation = nullptr;
    }

    void Set(const std::string& keyName);
    void Update(double deltaTime) override;

    // ゲッター
    double GetTime() const { return mCurrentTime; }

private:
    bool setSkeleton();

    // ボーンアニメーション計算
    void calculateBoneTransform(const Animation::Channel& channel, double time);
    Vector3 calculatePosition(const std::vector<Animation::KeyPosition>& keys, double time);
    Quaternion calculateRotation(const std::vector<Animation::KeyRotation>& keys, double time);
    Vector3 calculateScale(const std::vector<Animation::KeyScale>& keys, double time);
};