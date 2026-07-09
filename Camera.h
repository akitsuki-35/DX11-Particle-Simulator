/*============================================================
*	@file	 : Camera.h
*	@brief	 : カメラ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/26
*	@updated : 2026/06/02
*============================================================*/
#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

/*============================================================
*	@class	: Camera
*	@brief	: カメラ
*============================================================*/
class Camera : public GameObject
{
protected:
	Vector3 mTarget{}; // 注視点
	XMMATRIX mViewMatrix;

public:
	virtual ~Camera() = default;
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;

	XMMATRIX GetViewMatrix() const { return mViewMatrix; }

	virtual Vector3 GetForward() const override {
		Vector3 forward = mTarget - mPosition;
		forward.Normalize();

		return forward;
	}

	virtual Vector3 GetRight() const override {
		Vector3 forward = mTarget - mPosition;
		Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 right = Vector3::cross(up, forward);
		right.Normalize();

		return right;
	}
};

class TopCamera : public Camera
{
public:
	void Initialize() override;
	void Update() override;
};

#endif // CAMERA_H