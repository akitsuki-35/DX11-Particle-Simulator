/*============================================================
*	@file	 : Scene.h
*	@brief	 : シーン基底クラス
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2025/09/17
*	@updated : 2026/06/23
*============================================================*/
#ifndef SCENE_H
#define SCENE_H

/*============================================================
*	@class	: Scene
*	@brief	: シーン基底クラス
*============================================================*/
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update(double elapsedTime) = 0;
	virtual void Draw() const = 0;
};

#endif // SCENE_H