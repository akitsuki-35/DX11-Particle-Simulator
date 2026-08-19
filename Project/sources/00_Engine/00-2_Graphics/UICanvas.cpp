/*============================================================
*	@file	 : UICanvas.cpp
*	@brief	 : UIキャンバス設定
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/12
*	@updated : 2026/08/12
*============================================================*/
#include "UICanvas.h"
#include "DeviceManager.h"
#include "Elements.h"
#include <cassert>
using namespace DirectX;

bool UICanvas::CreateCanvas(UIStyle::Pivot pivot)
{
	std::array<Element::VERTEX3D, 4> vertex = UIStyle::Create(pivot);

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

	mPivot = pivot;

	return true;
}

void UICanvas::Bind() const
{
	ID3D11Buffer* vertexBuffer = _mVertexBuffer.Get();

	// 頂点バッファ設定
	UINT stride = sizeof(Element::VERTEX3D);
	UINT offset = 0;
	D3D11::DeviceManager::getInstance().GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	D3D11::DeviceManager::getInstance().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void UICanvas::Draw() const
{
	// 描画命令発行
	D3D11::DeviceManager::getInstance().GetContext()->Draw(4, 0);
}