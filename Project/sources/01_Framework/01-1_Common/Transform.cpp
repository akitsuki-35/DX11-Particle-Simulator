/*============================================================
*	@file	 : Transform.cpp
*	@brief	 : トランスフォーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#include "Transform.h"

using namespace DirectX;

DirectX::XMMATRIX Transform::createScaleMatrix() const
{
    // スケール行列作成
    XMMATRIX scale =XMMatrixScaling(mScale.x, mScale.y, mScale.z);

    return scale;
}

DirectX::XMMATRIX Transform::createRotationMatrix() const
{
    // 回転行列作成
    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);

    return rotation;
}

DirectX::XMMATRIX Transform::createTranslationMatrix() const
{
    // 移動行列作成
    XMMATRIX translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);

    return translation;
}

DirectX::XMMATRIX Transform::createBillboardRotation(const DirectX::XMMATRIX& view) const
{
    // ビルボード用回転行列作成
    XMMATRIX billboardView = XMMatrixInverse(nullptr, view);
    billboardView.r[3].m128_f32[0] = 0.0f;
    billboardView.r[3].m128_f32[1] = 0.0f;
    billboardView.r[3].m128_f32[2] = 0.0f;

    return billboardView;
}

void Transform::rebuildWorldMatrix(const DirectX::XMMATRIX& rotation) const
{
    // ワールド行列を更新
    XMMATRIX scale = createScaleMatrix();
    XMMATRIX translation = createTranslationMatrix();

    mWorldMatrix = scale * rotation * translation;

    mDirty = false;
}

DirectX::XMMATRIX Transform::GetWorldMatrix() const
{
    // 前のワールド行列から更新されていれば更新後のワールド行列を返す
    if (mDirty) {
        rebuildWorldMatrix(createRotationMatrix());
    }
    return mWorldMatrix;
}

DirectX::XMMATRIX Transform::GetBillboardMatrix(const DirectX::XMMATRIX& view) const
{
    // 前のワールド行列から更新されていれば更新後のワールド行列を返す
    rebuildWorldMatrix(createBillboardRotation(view));
    return mWorldMatrix;
}

Vector3 Transform::GetForward() const
{
    const DirectX::XMMATRIX& world = GetWorldMatrix();

    Vector3 forward{};
    XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&forward), world.r[2]);

    forward.Normalize();

    return forward;
}

Vector3 Transform::GetRight() const
{
    const DirectX::XMMATRIX& world = GetWorldMatrix();

    Vector3 right{};
    XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&right), world.r[0]);

    right.Normalize();

    return right;
}

Vector3 Transform::GetUp() const
{
    const DirectX::XMMATRIX& world = GetWorldMatrix();

    Vector3 up{};
    XMStoreFloat3(reinterpret_cast<DirectX::XMFLOAT3*>(&up), world.r[1]);

    up.Normalize();

    return up;
}
