/*============================================================
*	@file	 : Model.h
*	@brief	 : モデルリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/30
*	@updated : 2026/07/30
*============================================================*/
#pragma once

#include "Texture.h"
#include "ModelMesh.h"
#include "Skeleton.h"
#include "Elements.h"
#include <memory>
#include <vector>

/*============================================================
*	@class	: Model
*	@brief	: モデルリソース
*============================================================*/
class Model
{
	friend class ModelManager;
	friend class ModelRenderer;
	friend class AssimpLoader;

private:

	// モデル用マテリアル
	struct MATERIAL
	{
		Element::MATERIAL Material{};
		Texture* _Texture{};
	};

	std::vector<ModelMesh> mMeshes{}; // メッシュ
	std::vector<MATERIAL> mMaterials{}; // マテリアル
	Skeleton mSkeleton{}; // スケルトン
	std::vector<std::unique_ptr<Texture>> mTextures{}; // 埋め込みテクスチャ

public:
	void AddMesh(ModelMesh&& mesh);
	Skeleton& GetSkeleton() { return mSkeleton; }
};