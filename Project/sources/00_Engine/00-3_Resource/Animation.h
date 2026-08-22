/*============================================================
*	@file	 : Animation.h
*	@brief	 : アニメーションクリップ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Quaternion.h"
#include <vector>
#include <DirectXMath.h>

/*============================================================
*	@class	: Animation
*	@brief	: アニメーションクリップ
*============================================================*/
class Animation final
{
    friend class AssimpLoader;

public:
    // 移動キー
    struct KeyPosition
    {
        Vector3 Position{};
        double Time{};
    };

    // 回転キー
    struct KeyRotation
    {
        Quaternion Rotation{};
        double Time{};
    };

    // 拡大縮小キー
    struct KeyScale
    {
        Vector3 Scale{};
        double Time{};
    };

    // アニメーションチャンネル
    struct Channel
    {
        // ボーン番号
        int BoneIndex{ -1 };

        std::vector<KeyPosition> Positions{};
        std::vector<KeyRotation> Rotations{};
        std::vector<KeyScale> Scales{};
    };

private:
    double mDuration{}; // 総再生時間
    double mTicksPerSecond{}; // 1秒あたりのTick数

    // チャンネル
    std::vector<Channel> mChannels{};

public:
    void AddChannel(const Channel& channel);
    
    // ゲッター
    double GetDuration() const { return mDuration; }
    double GetTicksPerSecond() const { return mTicksPerSecond; }
    const std::vector<Channel>& GetChannels() const { return mChannels; }
};