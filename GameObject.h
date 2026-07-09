/*============================================================
*	@file	 : GameObject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/12
*	@updated : 2026/06/16
*============================================================*/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Main.h"
#include "Vector3.h"
#include "Component.h"
#include <sstream>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected: // 継承先からアクセス可能なメンバ変数

	int mLayer{ 1 }; // レイヤー番号
	float mCameraZ; // カメラからの距離（Zソート用）

	Vector3 mPosition{ 0.0f, 0.0f, 0.0f };
	Vector3 mRotation{ 0.0f, 0.0f, 0.0f };
	Vector3 mScale{ 1.0f, 1.0f, 1.0f };

	std::list<Component*> mComponents; // コンポーネント

	std::string mTag{};
	bool mIsDestroy{ false };

public:
	GameObject() = default;
	GameObject(const Vector3& position, const Vector3& rotation, const Vector3& scale, const std::string& tag, bool isDestroy = true) 
		: mPosition(position), mRotation(rotation), mScale(scale), mTag(tag), mIsDestroy(isDestroy) {}
	virtual ~GameObject() = default;

	void SetPosition(const Vector3& position) { mPosition = position; }
	void SetScale(const Vector3& scale) { mScale = scale; }

	void SetDestroy() { mIsDestroy = true; }
	bool Destroy() {
		if (mIsDestroy) {
			Finalize();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}

	virtual void Initialize() = 0;
	virtual void Finalize() {
		for (Component* component : mComponents) {
			component->Finalize();
			delete component;
		}
	}
	virtual void Update() {
		for (Component* component : mComponents) {
			component->Update();
		}
	}
	virtual void Draw() const {
		for (Component* component : mComponents) {
			component->Draw();
		}
	}

	template <typename T> // テンプレート関数
	T* AddComponent(GameObject* object) {
		T* component = new T(object);
		component->Initialize();
		mComponents.push_back(component);

		return component;
	}

	// ゲッター
	const int& GetLayer() const { return mLayer; }
	const float& GetCameraZ() const { return mCameraZ; }

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetRotation() const { return mRotation; }
	const Vector3& GetScale() const { return mScale; }

	// Z値計算
	void CalcCameraZ(Vector3 cameraPosition, Vector3 cameraForward) {
		Vector3 dir = mPosition - cameraPosition;
		mCameraZ = Vector3::dot(dir, cameraForward);
	}

	virtual Vector3 GetForward() const {
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[2]);
		return forward;
	}

	virtual Vector3 GetRight() const {
		DirectX::XMMATRIX r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z);

		Vector3 forward;
		XMStoreFloat3((XMFLOAT3*)&forward, r.r[0]);
		return forward;
	}

	const std::string& GetTag() const { return mTag; }
};

#endif // GAMEOBJECT_H