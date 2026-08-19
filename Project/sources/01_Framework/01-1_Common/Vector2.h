/*============================================================
*	@file	 : Vector2.h
*	@brief	 : 2次元ベクトルクラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/07/24
*============================================================*/
#pragma once

#include <cmath>
#include <DirectXMath.h>

/*============================================================
*	@class	: Vector2
*	@brief	: 2次元ベクトル
*============================================================*/
class Vector2
{
public:
	float x{};
	float y{};

public:
	constexpr Vector2() = default;

	constexpr Vector2(const Vector2& vector2)
		: x(vector2.x), y(vector2.y) {}
	constexpr Vector2(const float& x, const float& y)
		: x(x), y(y) {}
	constexpr Vector2(const DirectX::XMFLOAT2& float2)
		: x(float2.x), y(float2.y) {}

	/*------------------------------------------------------------
		代入
	------------------------------------------------------------*/
	Vector2& operator=(const Vector2& vector2) {
		x = vector2.x;
		y = vector2.y;
		return *this;
	}

	/*------------------------------------------------------------
		比較
	------------------------------------------------------------*/
	bool operator==(const Vector2& vector2) const {
		return x == vector2.x && y == vector2.y;
	}

	bool operator!=(const Vector2& vector2) const {
		return x != vector2.x || y != vector2.y;
	}

	/*------------------------------------------------------------
		ベクトルのゼロ化
	------------------------------------------------------------*/
	void Zero() {
		x = y = 0.0f;
	}

	/*------------------------------------------------------------
		ベクトルの反転
	------------------------------------------------------------*/
	Vector2 operator-() const {
		return Vector2(-x, -y);
	}

	/*------------------------------------------------------------
		加減算
	------------------------------------------------------------*/
	Vector2 operator+(const Vector2& vector2) const {
		return Vector2(x + vector2.x, y + vector2.y);
	}

	Vector2 operator-(const Vector2& vector2) const {
		return Vector2(x - vector2.x, y - vector2.y);
	}

	/*------------------------------------------------------------
		乗除算
	------------------------------------------------------------*/
	Vector2 operator*(float scalar) const {
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(float scalar) const {
		float oneOverA = 1.0f / scalar;
		return Vector2(x * oneOverA, y * oneOverA);
	}

	/*------------------------------------------------------------
		代入演算
	------------------------------------------------------------*/
	Vector2& operator+=(const Vector2& vector2) {
		x += vector2.x;
		y += vector2.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& vector2) {
		x -= vector2.x;
		y -= vector2.y;
		return *this;
	}

	Vector2& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}

	/*------------------------------------------------------------
		正規化
	------------------------------------------------------------*/
	void Normalize() {
		float magSq = x * x + y * y;
		if (magSq > 0.0f) {
			float oneOverMag = 1.0f / std::sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
		}
	}

	/*------------------------------------------------------------
		ベクトルの長さ取得
	------------------------------------------------------------*/
	float Length() const
	{
		return std::sqrt(x * x + y * y);
	}

	/*------------------------------------------------------------
		内積
	------------------------------------------------------------*/
	static float Dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}

	/*------------------------------------------------------------
		XMFLOAT2に変換
	------------------------------------------------------------*/
	DirectX::XMFLOAT2 ConvertToXMFLOAT2() const {
		return { x, y };
	}
};