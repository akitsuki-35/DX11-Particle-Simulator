/*============================================================
*	@file	 : Skeleton.h
*	@brief	 : ボーン構造体＆スケルトン
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/08/07
*============================================================*/
#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <DirectXMath.h>

/*============================================================
*	@class	: Skeleton
*	@brief	: ボーン構造体＆スケルトン
*============================================================*/
class Skeleton final
{
public:
    // ボーン構造体
    struct Bone
    {
        std::string Name{}; // ボーン名
        int ParentIndex{ -1 }; // 親ボーン
        DirectX::XMFLOAT4X4 Offset{}; // オフセット行列
        DirectX::XMFLOAT4X4 Local{}; // ローカル変換
        DirectX::XMFLOAT4X4 Global{}; // グローバル変換

        // バインドポーズ
        DirectX::XMFLOAT4X4 BindLocal{};
        DirectX::XMFLOAT4X4 BindGlobal{};
    };

private:
    std::unordered_map<std::string, int> mBoneMap{};
    std::vector<Bone> mBones{};

    std::vector<DirectX::XMFLOAT4X4>mSkinningMatrices{};
    DirectX::XMFLOAT4X4 mGlobalInverse{};

public:
    int AddBone(const Bone& bone);

    // ボーン取得
    int FindBone(const std::string& name) const;

    void Update();

    // バインドポーズ計算
    void CalculateBindPose();

    void SetGlobalInverse(const DirectX::XMFLOAT4X4& matrix){ mGlobalInverse = matrix; }

    // ゲッター
    int GetBoneIndex(const std::string& name);
    Bone& GetBone(size_t index) { return mBones[index]; }
    size_t GetBoneCount() const { return mBones.size(); }
    const std::vector<DirectX::XMFLOAT4X4>& GetSkinningMatrices() const { return mSkinningMatrices; }

private:
    void calculateBindGlobal(int index);
    void updateGlobal(int index);
    void updateSkinningMatrices();
};