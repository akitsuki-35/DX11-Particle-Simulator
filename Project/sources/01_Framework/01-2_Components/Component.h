/*============================================================
*	@file	 : Component.h
*	@brief	 : コンポーネント基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/19
*	@updated : 2026/08/04
*============================================================*/
#pragma once

/*============================================================
*	@class	: Component
*	@brief	: コンポーネント基底クラス
*============================================================*/
class Component
{
protected:
	class GameObject* _mOwner{ nullptr };

public:
	Component() {}
	Component(GameObject* owner)
		: _mOwner(owner){}
	virtual ~Component() = default;

	virtual void Initialize() {};
	virtual void Finalize() {};
	virtual void Update(double /*deltaTime*/) {};
	virtual void Draw() const {};
};