/*============================================================
*	@file	 : Box.h
*	@brief	 : 箱
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/16
*	@updated : 2026/06/16
*============================================================*/
#ifndef BOX_H
#define BOX_H

#include "GameObject.h"

/*============================================================
*	@class	: Box
*	@brief	: 箱
*============================================================*/
class Box : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

public:
	Box() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // BOX_H