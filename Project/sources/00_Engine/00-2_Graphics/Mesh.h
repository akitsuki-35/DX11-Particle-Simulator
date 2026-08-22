/*============================================================
*	@file	 : Mesh.h
*	@brief	 : ポリゴンメッシュ生成
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "MeshTypes.h"
#include <wrl/client.h>
#include <d3d11.h>

/*============================================================
*	@class	: Mesh
*	@brief	: ポリゴンメッシュ生成
*============================================================*/
class Mesh
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	// 頂点バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mVertexBuffer{};

	// インデックスバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> _mIndexBuffer{};

	UINT mStride{};
	UINT mVertexNum{};
	UINT mIndexNum{};
	bool mIsIndex{ false };

public:
	Mesh() = default;
	~Mesh() = default;

	bool CreatePlane(MeshType::Plane::Pivot pivot, MeshType::Plane::Axis axis);

	void Bind() const;
	void Draw() const;
};