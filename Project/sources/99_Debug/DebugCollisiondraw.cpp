/*============================================================
*	@file	 : debug_collisiondraw.cpp
*	@brief	 : コリジョン可視化
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/04/20
*	@updated : 2026/06/02
*============================================================*/
#include "DebugCollisiondraw.h"
#include "direct3d.h"
#include "shader2d.h"
#include "texture.h"
#include <iostream>
#include <memory>
using namespace DirectX;

/*------------------------------------------------------------
	グローバル変数定義
------------------------------------------------------------*/
static constexpr int CIRCLE_NUM_VERTEX{ 9 }; // 頂点数
static ID3D11Buffer* g_pCircleVertexBuffer{ nullptr }; // 頂点バッファ
static constexpr int BOX_NUM_VERTEX{ 5 }; // 頂点数
static ID3D11Buffer* g_pBoxVertexBuffer{ nullptr }; // 頂点バッファ
static Texture* g_pTexture{ nullptr };

/*------------------------------------------------------------
	頂点構造体
------------------------------------------------------------*/
struct Vertex
{
	XMFLOAT3 position; // 頂点座標
	XMFLOAT4 color; //色
	XMFLOAT2 texCoord;
};

void CollisionDrawInitialize()
{
#if defined(DEBUG) || defined(_DEBUG)
	g_pTexture = new Texture(L"Resources/Textures/Common/white.png");

	// サークルコリジョン頂点バッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * CIRCLE_NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Direct3DGetDevice()->CreateBuffer(&bd, NULL, &g_pCircleVertexBuffer);

	// ボックスコリジョン頂点バッファ生成
	bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * BOX_NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Direct3DGetDevice()->CreateBuffer(&bd, NULL, &g_pBoxVertexBuffer);
#endif
}

void CollisionDrawFinalize()
{
#if defined(DEBUG) || defined(_DEBUG)
	SAFE_RELEASE(g_pBoxVertexBuffer);
	SAFE_RELEASE(g_pCircleVertexBuffer);
	delete g_pTexture;
#endif
}

/*------------------------------------------------------------
	サークルコリジョン描画
------------------------------------------------------------*/
void CircleCollisionDraw(const DirectX::XMFLOAT2& center, const float& radius, const DirectX::XMFLOAT4& color)
{
	// 仮でボックス用の描画を流用しているため、デバッグ時は留意
#if defined(DEBUG) || defined(_DEBUG)
	g_pTexture->SetTexture();

	// シェーダーを描画パイプラインに設定
	Shader2DBeginLinear();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(g_pCircleVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	// 円の描画
	v[0].position = { center.x - (radius), center.y, 0.0f };
	v[1].position = { center.x - (radius * 0.75f), center.y - (radius * 0.75f), 0.0f };
	v[2].position = { center.x, center.y - (radius), 0.0f };
	v[3].position = { center.x + (radius * 0.75f), center.y - (radius * 0.75f), 0.0f };
	v[4].position = { center.x + (radius), center.y, 0.0f };
	v[5].position = { center.x + (radius * 0.75f), center.y + (radius * 0.75f), 0.0f };
	v[6].position = { center.x, center.y + (radius), 0.0f };
	v[7].position = { center.x - (radius * 0.75f), center.y + (radius * 0.75f), 0.0f };
	v[8].position = v[0].position;

	for (int i = 0; i < CIRCLE_NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	v[0].texCoord = { 0.0f, 0.5f };
	v[1].texCoord = { 0.25f, 0.25f };
	v[2].texCoord = { 0.5f, 0.0f };
	v[3].texCoord = { 0.75f, 0.25f };
	v[4].texCoord = { 1.0f, 0.5f };
	v[5].texCoord = { 0.75f, 0.75f };
	v[6].texCoord = { 0.5f, 1.0f };
	v[7].texCoord = { 0.25f, 0.75f };
	v[8].texCoord = v[0].texCoord;

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(g_pCircleVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &g_pCircleVertexBuffer, &stride, &offset);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(XMMatrixIdentity());

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(CIRCLE_NUM_VERTEX, 0);
#endif
}

/*------------------------------------------------------------
	ボックスコリジョン描画
------------------------------------------------------------*/
void BoxCollisionDraw(const DirectX::XMFLOAT2& center, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& color)
{
#if defined(DEBUG) || defined(_DEBUG)
	g_pTexture->SetTexture();

	// シェーダーを描画パイプラインに設定
	Shader2DBeginLinear();

	// 頂点バッファをロックする
	D3D11_MAPPED_SUBRESOURCE msr;
	Direct3DGetDeviceContext()->Map(g_pBoxVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得
	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み
	const float SCREEN_WIDTH = static_cast<float>(Direct3DGetBackBufferWidth());
	const float SCREEN_HEIGHT = static_cast<float>(Direct3DGetBackBufferHeight());

	//四角形の描画
	v[0].position = { center.x - (size.x / 2), center.y - (size.y / 2), 0.0f };
	v[1].position = { center.x + (size.x / 2), center.y - (size.y / 2), 0.0f };
	v[2].position = { center.x + (size.x / 2), center.y + (size.y / 2), 0.0f };
	v[3].position = { center.x - (size.x / 2), center.y + (size.y / 2), 0.0f };
	v[4].position = v[0].position;

	for (int i = 0; i < BOX_NUM_VERTEX; i++)
	{
		v[i].color = color;
	}

	v[0].texCoord = { 0.0f, 0.0f };
	v[1].texCoord = { 1.0f, 0.0f };
	v[2].texCoord = { 1.0f, 1.0f };
	v[3].texCoord = { 0.0f, 1.0f };
	v[4].texCoord = v[0].texCoord;

	// 頂点バッファのロックを解除
	Direct3DGetDeviceContext()->Unmap(g_pBoxVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Direct3DGetDeviceContext()->IASetVertexBuffers(0, 1, &g_pBoxVertexBuffer, &stride, &offset);

	// 頂点シェーダーにワールド変換行列を設定
	Shader2DSetWorldMatrix(XMMatrixIdentity());

	// 頂点シェーダーにプロジェクション変換行列を設定
	Shader2DSetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	Shader2DSetColor({ 1.0f,1.0f,1.0f,1.0f });

	// プリミティブトポロジ設定
	Direct3DGetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// ポリゴン描画命令発行
	Direct3DGetDeviceContext()->Draw(BOX_NUM_VERTEX, 0);
#endif
}