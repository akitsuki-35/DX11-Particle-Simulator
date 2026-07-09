/*============================================================
*	@file	 : Collision.cpp
*	@brief	 : 当たり判定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/19
*	@updated : 2026/06/02
*============================================================*/
#include "Collision.h"
#include "DebugCollisiondraw.h"
#include "Texture.h"
#include "Sprite.h"
#include <cmath>
using namespace DirectX;

/*------------------------------------------------------------
	ローカル関数 プロトタイプ宣言
------------------------------------------------------------*/
float GetDistance(const XMFLOAT2& targetA, const XMFLOAT2& targetB);

/*------------------------------------------------------------
	サークルコリジョン
------------------------------------------------------------*/
bool Collision::Circle::IsOverlap(const Circle* target) const
{
    // 円 * 円
    // 中心座標同士の距離を取得
    float centerDistance = GetDistance(target->center, center);

    // 半径が重なっているかを判定
    if (centerDistance <= radius + target->radius) {
        return true;
    }

    return false;
}

bool Collision::Circle::IsOverlap(const Box* target) const
{
    // 円 * 四角
    // 中心座標同士の距離を取得
    float distance[4] = {
    GetDistance(target->min, center), GetDistance({target->max.x, target->min.y}, center),
    GetDistance({target->min.x, target->max.y}, center), GetDistance(target->max, center),
    };

    // 円と四角が重なっているかを判定
    return (center.x <= target->max.x + radius) && (center.x >= target->min.x - radius)
        && (center.y <= target->max.y) && (center.y >= target->min.y)

        || (center.x <= target->max.x) && (center.x >= target->min.x)
        && (center.y <= target->max.y + radius) && (center.y >= target->min.y - radius)

        || (distance[0] <= radius) || (distance[1] <= radius)
        || (distance[2] <= radius) || (distance[3] <= radius);
}

bool Collision::Circle::IsOverlap(const DirectX::XMFLOAT2& target) const
{
    // つくりかけ
    //float centerDistance = GetDistance(target, center);

    //if (centerDistance <= radius + target.x) {
    //    return true;
    //}

    return false;
}

/*------------------------------------------------------------
	デバッグ用描画関数
------------------------------------------------------------*/
void Collision::Circle::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    CircleCollisionDraw(center, radius, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}

/*------------------------------------------------------------
	ボックスコリジョン
------------------------------------------------------------*/
bool Collision::Box::IsOverlap(const Circle* target) const
{
    // 四角 * 円
    // 円コリジョン側の判定を利用
    return target->IsOverlap(this);
}

bool Collision::Box::IsOverlap(const Box* target) const
{
    // 四角 * 四角
    // minとmaxが重なっているかを判定
    return min.x < target->max.x
        && max.x > target->min.x
        && min.y < target->max.y
        && max.y > target->min.y;
}

bool Collision::Box::IsOverlap(const DirectX::XMFLOAT2& target) const
{
    // 四角 * 点（マウスカーソル用）
    // 点座標が四角の範囲内にあるかを判定
    return min.x < target.x
        && max.x > target.x
        && min.y < target.y
        && max.y > target.y;
}

/*------------------------------------------------------------
    デバッグ用描画関数
------------------------------------------------------------*/
void Collision::Box::Draw() const
{
#if defined(DEBUG) || defined(_DEBUG)
    BoxCollisionDraw(center, collisionSize, { 0.0f, 1.0f, 0.0f, 1.0f });
#endif
}

/*------------------------------------------------------------
	距離の取得
------------------------------------------------------------*/
float GetDistance(const XMFLOAT2& targetA, const XMFLOAT2& targetB)
{
    XMFLOAT2 distance{ targetA.x - targetB.x, targetA.y - targetB.y };
    return std::sqrt((distance.x * distance.x) + (distance.y * distance.y));
}