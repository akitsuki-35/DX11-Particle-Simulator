/*============================================================
*	@file	 : Sky.h
*	@brief	 : スカイドーム
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/09
*	@updated : 2026/06/09
*============================================================*/
#ifndef SKY_H
#define SKY_H

#include "GameObject.h"

/*============================================================
*	@class	: Sky
*	@brief	: スカイドーム
*============================================================*/
class Sky : public GameObject
{
private:
	Vector3 mVelocity{ 0.0f, 0.0f, 0.0f };
	Vector3 mAccel{ 0.0f, 0.0f, 0.0f };

	ID3D11InputLayout* _mVertexLayout{}; // 頂点レイアウト
	ID3D11VertexShader* _mVertexShader{}; // 頂点シェーダー
	ID3D11PixelShader* _mPixelShader{}; // ピクセルシェーダー

public:
	Sky() = default;

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() const override;
};

#endif // Sky_H