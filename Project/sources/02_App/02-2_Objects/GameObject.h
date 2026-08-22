/*============================================================
*	@file	 : GameObject.h
*	@brief	 : 3Dゲームオブジェクト基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/12
*	@updated : 2026/07/21
*============================================================*/
#pragma once

#include "Vector3.h"
#include "Component.h"
#include "Transform.h"
#include <sstream>
#include <memory>
#include <vector>
#include <DirectXMath.h>

/*============================================================
*	@class	: GameObject
*	@brief	: ゲームオブジェクト基底クラス
*============================================================*/
class GameObject
{
protected:
	// トランスフォーム
	Transform mTransform{};

	// コンポーネント
	std::vector<std::unique_ptr<Component>> mComponents{};

	std::string mTag{};

	// 削除フラグ
	bool mIsDestroy{ false };

public:
	GameObject() = default;
	virtual ~GameObject() = default;

	void SetDestroy() { mIsDestroy = true; }
	bool Destroy() {			
		if (mIsDestroy) {
			// 削除フラグがオンなら削除
			Finalize();
			return true;
		}
		else {
			return false;
		}
	}

	virtual void Initialize() = 0;

	virtual void Finalize() {
		for (const auto& component : mComponents) {
			component->Finalize();
		}
		mComponents.clear();
	}

	virtual void Update(double deltaTime) {
		for (const auto& component : mComponents) {
			component->Update(deltaTime);
		}
	}

	virtual void Draw() const {
		for (const auto& component : mComponents) {
			component->Draw();
		}
	}

	// コンポーネント追加
	template <typename T>
	T* AddComponent(GameObject* object) {
		auto component = std::make_unique<T>(object);
		T* ptr = component.get();

		mComponents.push_back(std::move(component));
		ptr->Initialize();

		return ptr;
	}

	// コンポーネント取得
	template <typename T>
	T* GetComponent() const {
		for (const auto& component : mComponents) {
			T* find = dynamic_cast<T*>(component.get());
			if (find) return find;
		}
		return nullptr;
	}

	// ゲッター
	const Transform& GetTransform() const { return mTransform; }
	const Vector3& GetPosition() const { return mTransform.GetPosition(); }
	const Vector3& GetRotation() const { return mTransform.GetRotation(); }
	const Vector3& GetScale() const { return mTransform.GetScale(); }

	// セッター
	GameObject& SetPosition(const Vector3& position) {
		mTransform.SetPosition(position);
		return *this;
	}

	GameObject& SetRotation(const Vector3& rotation) {
		mTransform.SetRotation(rotation);
		return *this;
	}

	GameObject& SetScale(const Vector3& scale) {
		mTransform.SetScale(scale);
		return *this;
	}

	const std::string& GetTag() const { return mTag; }
};