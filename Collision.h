/*============================================================
*	@file	 : Collision.h
*	@brief	 : 当たり判定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/29
*	@updated : 2026/06/02
*============================================================*/
#ifndef COLLISION_H
#define COLLISION_H

#include <DirectXMath.h>

/*============================================================
*	@namespace	: Collision
*	@brief		: 衝突防止用ネームスペース
* 
* 　※using namespaceしないこと
*============================================================*/
namespace Collision {
	class Circle;
	class Box;
}

/*============================================================
*	@class	: CollisionBase
*	@brief	: コリジョン基底クラス
*============================================================*/
class CollisionBase
{
protected:
	DirectX::XMFLOAT2 position{}; // コリジョン左上座標;
	DirectX::XMFLOAT2 center{}; // コリジョン中心座標
	DirectX::XMFLOAT2 collisionSize{}; // コリジョンサイズ

public:
	CollisionBase(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: position(position), collisionSize(collisionSize) {
		SetCenter(position);
	}
	virtual ~CollisionBase() = default;

	// 中心座標更新
	void SetCenter(const DirectX::XMFLOAT2& offset) {
		center = { offset.x + collisionSize.x / 2, offset.y + collisionSize.y / 2 };
	}

	// サイズ更新
	void SetSize(const DirectX::XMFLOAT2& size) {
		collisionSize = size;
		SetCenter(position);
	}

	// コリジョン移動
	virtual void Move(const DirectX::XMFLOAT2& currentPos) {
		DirectX::XMFLOAT2 newPos = currentPos;
		SetCenter(newPos);
	}

	// 中心座標取得
	virtual const DirectX::XMFLOAT2& GetCenter() const { return center; }

	// 各種コリジョンとの当たり判定（継承先で処理）
	virtual bool IsOverlap(const Collision::Circle*) const { return false; }
	virtual bool IsOverlap(const Collision::Box*) const { return false; }
	virtual bool IsOverlap(const DirectX::XMFLOAT2&) const { return false; }

	// 描画（デバッグ用）
	virtual void Draw() const {}
};

/*============================================================
*	@class	: Circle
*	@brief	: サークルコリジョン
*============================================================*/
class Collision::Circle : public CollisionBase
{
	friend Box;

private:
	float radius{};

public:
	Circle(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: CollisionBase(position, collisionSize) {
		if (collisionSize.x / 2 <= collisionSize.y / 2) {
			radius = collisionSize.x / 2;
		}
		else {
			radius = collisionSize.y / 2;
		}
	}

	// 各種コリジョンとの当たり判定
	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;
	virtual bool IsOverlap(const DirectX::XMFLOAT2& target) const override;

	// コリジョン移動
	virtual void Move(const DirectX::XMFLOAT2& currentPos) override {
		SetCenter(currentPos);
	}

	// 描画（デバッグ用）
	void Draw() const override;
};

/*============================================================
*	@class	: Box
*	@brief	: ボックスコリジョン
*============================================================*/
class Collision::Box : public CollisionBase
{
	friend Circle;

private:
	DirectX::XMFLOAT2 min{};
	DirectX::XMFLOAT2 max{};

public:
	Box(const DirectX::XMFLOAT2& position, const DirectX::XMFLOAT2& collisionSize)
		: CollisionBase(position, collisionSize) {
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	// 各種コリジョンとの当たり判定
	bool IsOverlap(const Circle* target) const override;
	bool IsOverlap(const Box* target) const override;
	virtual bool IsOverlap(const DirectX::XMFLOAT2& target) const override;

	// コリジョン移動
	void Move(const DirectX::XMFLOAT2& currentPos) override {
		float x = position.x - currentPos.x;
		float y = position.y - currentPos.y;

		x = currentPos.x - x;
		y = currentPos.y - y;

		position = { x, y };
		SetCenter(position);

		//SetCenter(currentPos);
		min = { center.x - (collisionSize.x / 2), center.y - (collisionSize.y / 2) };
		max = { center.x + (collisionSize.x / 2), center.y + (collisionSize.y / 2) };
	}

	// 描画（デバッグ用）
	void Draw() const override;
};

#endif // COLLISION_H