/*============================================================
*	@file	 : vector3.h
*	@brief	 : 3次元ベクトルクラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/23
*	@updated : 2026/06/16
*============================================================*/
#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

/*============================================================
*	@class	: Vector3
*	@brief	: 3次元ベクトル
*============================================================*/
class Vector3
{
public:
	float x, y, z;

public:
	Vector3() = default;

	Vector3(const Vector3& vector3)
		: x(vector3.x), y(vector3.y), z(vector3.z){}
	Vector3(const float& x, const float& y, const float& z)
		: x(x), y(y), z(z) {}
	
/*------------------------------------------------------------
	代入
------------------------------------------------------------*/
	Vector3& operator = (const Vector3& vector3) {
		x = vector3.x;
		y = vector3.y;
		z = vector3.z;
		return *this;
	}

/*------------------------------------------------------------
	比較
------------------------------------------------------------*/
	bool operator == (const Vector3 & vector3) const{
		return x == vector3.x && y == vector3.y && z == vector3.z;
	}

	bool operator != (const Vector3& vector3) const {
		return x != vector3.x || y != vector3.y || z != vector3.z;
	}

/*------------------------------------------------------------
	ベクトルのゼロ化
------------------------------------------------------------*/
	void Zero() {
		x = y = z = 0.0f;
	}

/*------------------------------------------------------------
	ベクトルの反転
------------------------------------------------------------*/
	Vector3 operator - () const {
		return Vector3(-x, -y, -z);
	}

/*------------------------------------------------------------
	加減算
------------------------------------------------------------*/
	Vector3 operator + (const Vector3& vector3) const {
		return Vector3(x + vector3.x, y + vector3.y, z + vector3.z);
	}

	Vector3 operator - (const Vector3& vector3) const {
		return Vector3(x - vector3.x, y - vector3.y, z - vector3.z);
	}

/*------------------------------------------------------------
	乗余算
------------------------------------------------------------*/
	Vector3 operator * (float scalar) const {
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	Vector3 operator / (float scalar) const {
		float oneOverA = 1.0f / scalar;
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}
	
/*------------------------------------------------------------
	代入演算
------------------------------------------------------------*/
	Vector3& operator += (const Vector3& vector3) {
		x += vector3.x;
		y += vector3.y;
		z += vector3.z;
		return *this;
	}

	Vector3& operator -= (const Vector3& vector3) {
		x -= vector3.x;
		y -= vector3.y;
		z -= vector3.z;
		return *this;
	}

	Vector3& operator *= (float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector3& operator /= (float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

/*------------------------------------------------------------
	正規化
------------------------------------------------------------*/
	void Normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) {
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}

/*------------------------------------------------------------
	ベクトルの長さ取得
------------------------------------------------------------*/
	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

/*------------------------------------------------------------
	内積
------------------------------------------------------------*/
	float operator * (const Vector3& vector3) const {
		return x * vector3.x + y * vector3.y + z * vector3.z;
	}

	static float dot(Vector3& a, Vector3& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

/*------------------------------------------------------------
	外積
------------------------------------------------------------*/
	static Vector3 cross(const Vector3& a, const Vector3& b) {
		return Vector3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	}
};

#endif // VECTOR3_H