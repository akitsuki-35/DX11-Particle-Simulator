/*============================================================
*	@file	 : Mesh.h
*	@brief	 : ポリゴンメッシュ生成
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/24
*	@updated : 2026/08/04
*============================================================*/
#include "Mesh.h"
#include "DeviceManager.h"
#include "Elements.h"
#include <cassert>
using namespace DirectX;

bool Mesh::CreatePlane(MeshType::Plane::Pivot pivot, MeshType::Plane::Axis axis)
{
	// 頂点情報定義
	MeshType::Plane::DESC desc{};
	desc.pivot = pivot;
	desc.axis = axis;

	std::array<Element::VERTEX3D, 4> vertex = MeshType::Plane::Create(desc);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Element::VERTEX3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex.data();

	D3D11::DeviceManager::getInstance().GetDevice()->CreateBuffer(&bd, &sd, _mVertexBuffer.GetAddressOf());

	assert(_mVertexBuffer);

	return true;
}

void Mesh::Bind() const
{
	ID3D11Buffer* vertexBuffer = _mVertexBuffer.Get();

	// 頂点バッファ設定
	UINT stride = sizeof(Element::VERTEX3D);
	UINT offset = 0;
	D3D11::DeviceManager::getInstance().GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Mesh::Draw() const
{
	// 描画命令発行
	D3D11::DeviceManager::getInstance().GetContext()->Draw(4, 0);
}
