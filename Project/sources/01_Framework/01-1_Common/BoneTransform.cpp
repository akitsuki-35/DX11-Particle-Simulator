/*============================================================
*	@file	 : BoneTransform.cpp
*	@brief	 : ボーン用トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "BoneTransform.h"

DirectX::XMMATRIX BoneTransform::ToMatrix() const
{
    DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
    DirectX::XMMATRIX rotation = Rotation.ToMatrix();
    DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);

    return scale * rotation * translation;
}
