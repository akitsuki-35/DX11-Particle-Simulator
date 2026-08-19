/*============================================================
*	@file	 : BufferManager.h
*	@brief	 : 定数バッファ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/14
*	@updated : 2026/08/04
*============================================================*/
#pragma once

#include "Elements.h"
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>

class Skeleton;

namespace D3D11 {
/*============================================================
*	@class	: BufferManager
*	@brief	: 定数バッファ管理
*============================================================*/
	class BufferManager final
	{
		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

	/*--------------------------------------------------
		Singleton用
	----------------------------------------------------*/
	public:
		static BufferManager& getInstance() {
			static BufferManager instance;
			return instance;
		}

	private:
		BufferManager() = default;
		BufferManager(const BufferManager&) = delete;

		BufferManager& operator=(const BufferManager&) = delete;
		BufferManager(BufferManager&&) = delete;

		BufferManager& operator=(BufferManager&&) = delete;
		~BufferManager() {};

	/*--------------------------------------------------
		メンバ変数・メンバ関数
	----------------------------------------------------*/
	private:
		// 定数バッファ
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mWorld{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mView{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mProjection{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mMaterial{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mLight{};
		Microsoft::WRL::ComPtr<ID3D11Buffer> _mBones{};

	public:
		void Initialize();

	private:
		// 定数バッファ生成
		Microsoft::WRL::ComPtr<ID3D11Buffer> generateBuffer(UINT size);
		Microsoft::WRL::ComPtr<ID3D11Buffer> generateInstanceBuffer(UINT size);

	public:
		// セッター
		void Set2DMatrix();
		void SetWorldMatrix(DirectX::XMMATRIX worldMatrix);
		void SetViewMatrix(DirectX::XMMATRIX viewMatrix);
		void SetProjectionMatrix(DirectX::XMMATRIX projectionMatrix);
		void SetMaterial(Element::MATERIAL material);
		void SetLight(Element::LIGHT light);
		void SetBoneMatrices(const Skeleton& skeleton);

		// ゲッター
		ID3D11Buffer* GetWorldBuffer() const { return _mWorld.Get(); }
		ID3D11Buffer* GetViewBuffer() const { return _mView.Get(); }
		ID3D11Buffer* GetProjectionBuffer() const { return _mProjection.Get(); }
		ID3D11Buffer* GetMaterialBuffer() const { return _mMaterial.Get(); }
		ID3D11Buffer* GetLightBuffer() const { return _mLight.Get(); }
		ID3D11Buffer* GetBoneBuffer() const { return _mBones.Get(); }
	};
}