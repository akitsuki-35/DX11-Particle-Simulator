/*============================================================
*	@file	 : BoneTransform.h
*	@brief	 : ボーン用トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/07
*	@updated : 2026/09/30
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Quaternion.h"

/*============================================================
*	@class	: BoneTransform
*	@brief	: ボーン用トランスフォーム
*============================================================*/
class BoneTransform
{
public:
    Vector3 mPosition{};
    Quaternion mRotation{};
    Vector3 mScale{ 1.0f,1.0f,1.0f };

    DirectX::XMMATRIX ToMatrix() const;
};