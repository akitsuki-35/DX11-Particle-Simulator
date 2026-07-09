/*============================================================
*	@file	 : Field.cpp
*	@brief	 : 3Dポリゴン表示
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/28
*	@updated : 2026/06/09
*============================================================*/
#include "Main.h"
#include "Field.h"
#include "Renderer.h"

Field::Field(const wchar_t* pFileName)
{
	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(pFileName, WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &_mTexture);
	assert(_mTexture);
}

void Field::Initialize()
{
	mLayer = 1;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-30.0f, 0.0f, 30.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(30.0f, 0.0f, 30.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-30.0f, 0.0f, -30.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(30.0f, 0.0f, -30.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &_mVertexBuffer);

	// テクスチャ読込
	TexMetadata metaData;
	ScratchImage image;
	LoadFromWICFile(L"Resources\\Textures\\glass.jpg", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &_mTexture);
	assert(_mTexture);

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");
}

void Field::Finalize()
{
	if (_mTexture) _mTexture->Release();

	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();
	_mVertexBuffer->Release();

	GameObject::Finalize();
}

void Field::Update()
{
	GameObject::Update();
}

void Field::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(_mVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(_mPixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX w, s, r, t;
	s = XMMatrixScaling(mScale.x, mScale.y, mScale.z); // 拡大縮小
	r = XMMatrixRotationRollPitchYaw(mRotation.x, mRotation.y, mRotation.z); // 回転
	t = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z); // 平行移動
	w = s * r * t;
	Renderer::SetWorldMatrix(w);

	// マテリアル設定
	MATERIAL material{};
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	if (_mTexture)material.TextureEnable = true;
	else material.TextureEnable = false;
	Renderer::SetMaterial(material);

	// テクスチャ設定
	if (_mTexture) {
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &_mTexture);
	}

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &_mVertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// 描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	GameObject::Draw();
}