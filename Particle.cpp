/*============================================================
*	@file	 : particle.cpp
*	@brief	 : パーティクル
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/06/18
*	@updated : 2026/06/18
*============================================================*/
#include "Main.h"
#include "Particle.h"
#include "BezierCurve.h"
#include "Player.h"
#include "Renderer.h"
#include "Game.h"
#include "Camera.h"
#include "Input.h"

// ImGui
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

/*============================================================
	通常パーティクル
*============================================================*/
void Particle::Initialize()
{
	mLayer = 2;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
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
	LoadFromWICFile(L"Resources\\Textures\\Common\\particle.png", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &_mTexture);
	assert(_mTexture);

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");

	// 構造体初期化
	for (int i = 0; i < PARTICLE_MAX; i++) {
		mParticle[i].enable = false;
	}
}

void Particle::Finalize()
{
	if (_mTexture) _mTexture->Release();

	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();
	_mVertexBuffer->Release();
}

void Particle::Update()
{
	float dt = 1.0f / 60.0f;
	Vector3 gravity{ 0.0f, -30.0f, 0.0f };

	int count = 100;

	// オブジェクト後方
	Vector3 back{};

	if (mObject) {
		// オブジェクト座標取得
		mPosition = mObject->GetPosition();

		// オブジェクト後方取得
		back = mObject->GetForward() * -1;
	}
	else {
		// オブジェクトが存在しなければ0にする
		back = { 0.0f, 0.0f, 0.0f };
	}

	if (Input::GetKeyTrigger(VK_SPACE)) {
		// パーティクル発射
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!mParticle[i].enable) {
				mParticle[i].enable = true;
				mParticle[i].life = 60;
				mParticle[i].position = mPosition;
				mParticle[i].velocity = { ((float)rand() / RAND_MAX - 0.5f) * 20.0f,
					((float)rand() / RAND_MAX) * 20.0f,
					((float)rand() / RAND_MAX - 0.5f) * 20.0f };
				mParticle[i].accel = back * 50.0f;

				float scale = ((float)rand() / RAND_MAX - 0.5f) * 5.0f;

				mParticle[i].scale = { scale, scale, scale };

				count--;
				if (count <= 0) {
					break;
				}
			}
		}
	}

	// パーティクル更新
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {
			mParticle[i].velocity += mParticle[i].accel * dt;
			mParticle[i].velocity += gravity * dt; // 重力
			mParticle[i].velocity += mParticle[i].velocity * -1.0f * dt; // 抵抗
			mParticle[i].position += mParticle[i].velocity * dt;
			
			mParticle[i].life--;

			if (mParticle[i].life <= 0) {

				mParticle[i].enable = false;
			}
		}
	}
}

void Particle::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(_mVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(_mPixelShader, NULL, 0);

	// ビルボード用マトリクス
	Camera* camera = Game::GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX invView = XMMatrixInverse(NULL, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// マテリアル設定
	MATERIAL material{};
	material.Diffuse = XMFLOAT4(mMainColor);
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

	// 深度バッファ無効化
	Renderer::SetDepthEnable(false);

	// 加算合成
	Renderer::SetAddBrendEnable(true);

	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {

			// マトリクス設定
			XMMATRIX w, s, r, t;
			s = XMMatrixScaling(mParticle[i].scale.x, mParticle[i].scale.y,
				mParticle[i].scale.z); // 拡大縮小	
			t = XMMatrixTranslation(mParticle[i].position.x, 
				mParticle[i].position.y, mParticle[i].position.z); // 平行移動
			w = s * invView * t;
			Renderer::SetWorldMatrix(w);

			// 描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	
	// マテリアル設定
	material.Diffuse = XMFLOAT4(mSubColor);
	if (_mTexture)material.TextureEnable = true;
	else material.TextureEnable = false;
	Renderer::SetMaterial(material);

	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {

			// マトリクス設定
			XMMATRIX w, s, r, t;
			s = XMMatrixScaling(mParticle[i].scale.x - 0.5f, mParticle[i].scale.y - 0.5f,
				mParticle[i].scale.z - 0.5f); // 拡大縮小	
			t = XMMatrixTranslation(mParticle[i].position.x,
				mParticle[i].position.y, mParticle[i].position.z); // 平行移動
			w = s * invView * t;
			Renderer::SetWorldMatrix(w);

			// 描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}

	// 設定を元に戻す
	Renderer::SetDepthEnable(true);
	Renderer::SetAddBrendEnable(false);
}

/*============================================================
	ベジエ曲線 × パーティクル
*============================================================*/
void ParticleBezier::Initialize()
{
	mLayer = 2;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
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
	LoadFromWICFile(L"Resources\\Textures\\Common\\particle.png", WIC_FLAGS_NONE, &metaData, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metaData, &_mTexture);
	assert(_mTexture);

	// シェーダー読込
	Renderer::CreateVertexShader(&_mVertexShader, &_mVertexLayout, "Resources\\Shaders\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&_mPixelShader, "Resources\\Shaders\\unlitTexturePS.cso");

	// 構造体初期化
	for (int i = 0; i < PARTICLE_MAX; i++) {
		mParticle[i].enable = false;
	}

	// ベジエ曲線初期化
	_mBezier = new BezierCurve();
}

void ParticleBezier::Finalize()
{
	delete _mBezier;

	if (_mTexture) _mTexture->Release();

	_mPixelShader->Release();
	_mVertexShader->Release();
	_mVertexLayout->Release();
	_mVertexBuffer->Release();
}

void ParticleBezier::Update()
{
	float dt = 1.0f / 60.0f;
	Vector3 gravity{ 0.0f, -9.8f, 0.0f };

	// パーティクル発射数
	int count = Count;
	
	// 全体フレームをセット
	_mBezier->SetFrameMax(Life);

	// ベジエ曲線再計算
	_mBezier->CalcBezier();

	// 現フレームのベジエ曲線上の画像を取得
	_mBezier->Update();
	mPosition = _mBezier->GetBezierPoint(_mBezier->GetFrame());

	// インターバル減少
	mInterval -= dt;

	if (mInterval <= 0.0) {
		// パーティクル発射
		for (int i = 0; i < PARTICLE_MAX; i++) {
			if (!mParticle[i].enable) {
				mParticle[i].enable = true;
				mParticle[i].life = Life;
				mParticle[i].position = mPosition;

				// 散布
				mParticle[i].velocity = { ((float)rand() / RAND_MAX - 0.5f) * 20.0f,
					((float)rand() / RAND_MAX) * 20.0f,
					((float)rand() / RAND_MAX - 0.5f) * 20.0f };

				mParticle[i].accel = { 0.0f, 0.0f, 0.0f };

				// t初期化
				mParticle[i].t = 0;

				// スケールランダム
				float scale = ((float)rand() / RAND_MAX - 0.5f) * 5.0f;

				mParticle[i].scale = { scale, scale, scale };

				count--;
				if (count <= 0) {
					break;
				}
			}
		}

		mInterval = Interval;
	}

	// パーティクル更新
	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {
			// tを更新
			mParticle[i].t++;
			if (mParticle[i].t >= Life) {
				mParticle[i].enable = false;
				continue;
			}

			// 座標計算
			mParticle[i].velocity += mParticle[i].accel * dt; // 加速度
			mParticle[i].velocity += gravity * dt; // 重力
			mParticle[i].velocity += mParticle[i].velocity * 0.0f * dt; // 抵抗
			mParticle[i].position += mParticle[i].velocity * dt;

			mParticle[i].life--;
			if (mParticle[i].life <= 0) {

				mParticle[i].enable = false;
			}
		}
	}
}

void ParticleBezier::Draw() const
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(_mVertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(_mVertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(_mPixelShader, NULL, 0);

	// ビルボード用マトリクス
	Camera* camera = Game::GetGameObject<Camera>();
	XMMATRIX view = camera->GetViewMatrix();
	XMMATRIX invView = XMMatrixInverse(NULL, view);
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	// マテリアル設定
	MATERIAL material{};
	material.Diffuse = XMFLOAT4(mMainColor);
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

	// 深度バッファ無効化
	Renderer::SetDepthEnable(false);

	// 加算合成
	Renderer::SetAddBrendEnable(true);

	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {

			// マトリクス設定
			XMMATRIX w, s, r, t;
			s = XMMatrixScaling(mParticle[i].scale.x, mParticle[i].scale.y,
				mParticle[i].scale.z); // 拡大縮小	
			t = XMMatrixTranslation(mParticle[i].position.x,
				mParticle[i].position.y, mParticle[i].position.z); // 平行移動
			w = s * invView * t;
			Renderer::SetWorldMatrix(w);

			// 描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}

	// マテリアル設定
	material.Diffuse = XMFLOAT4(mSubColor);
	if (_mTexture)material.TextureEnable = true;
	else material.TextureEnable = false;
	Renderer::SetMaterial(material);

	for (int i = 0; i < PARTICLE_MAX; i++) {
		if (mParticle[i].enable) {

			// マトリクス設定
			XMMATRIX w, s, r, t;
			s = XMMatrixScaling(mParticle[i].scale.x - 0.5f, mParticle[i].scale.y - 0.5f,
				mParticle[i].scale.z - 0.5f); // 拡大縮小	
			t = XMMatrixTranslation(mParticle[i].position.x,
				mParticle[i].position.y, mParticle[i].position.z); // 平行移動
			w = s * invView * t;
			Renderer::SetWorldMatrix(w);

			// 描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}

	// 設定を元に戻す
	Renderer::SetDepthEnable(true);
	Renderer::SetAddBrendEnable(false);
}