/*============================================================
*	@file	 : UICanvas.h
*	@brief	 : UIキャンバス設定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#pragma once

#include "UIStyle.h"
#include <wrl/client.h>
#include <d3d11.h>

/*============================================================
*	@class	: UICanvas
*	@brief	: UI用キャンバス
*============================================================*/
class UICanvas
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// ピボット
	UIStyle::Pivot mPivot{ UIStyle::Pivot::LeftTop };

	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mVertexBuffer{};

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mIndexBuffer{};

	UINT mStride{};
	UINT mVertexNum{};
	UINT mIndexNum{};
	bool mIsIndex{ false };

public:
	UICanvas() = default;
	~UICanvas() = default;

	bool CreateCanvas(UIStyle::Pivot pivot);

	void Bind() const;
	void Draw() const;

	// ゲッター
	UIStyle::Pivot GetPivot() const { return mPivot; }
};