/*------------------------------------------------------------
	シェーダー用構造体・バッファ定義
------------------------------------------------------------*/
/*------------------------------------------------------------
	構造体定義
------------------------------------------------------------*/
// VS構造体
struct VS_IN
{
    float4 Position : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
	
    uint4 BoneIndices : BLENDINDICES;
    float4 BoneWeights : BLENDWEIGHT;
};

// PS構造体
struct PS_IN
{
    float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
    float4 Diffuse : COLOR0;
    float2 TexCoord : TEXCOORD0;
};

// マテリアル
struct MATERIAL
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emission;
    float Shininess;
    int TextureEnable;
    float2 Dummy;
};

// ライト
struct LIGHT
{
    int Enable;
    float Dummy;
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

/*------------------------------------------------------------
	バッファ定義
------------------------------------------------------------*/
// ワールド行列
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

// ビュー行列
cbuffer ViewBuffer : register(b1)
{
    matrix View;
}

// プロジェクション行列
cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

// マテリアル
cbuffer MaterialBuffer : register(b3)
{
    MATERIAL Material;
}

// ライト
cbuffer LightBuffer : register(b4)
{
    LIGHT Light;
}

// カメラ
cbuffer CameraBuffer : register(b5)
{
    float4 CameraPosition;
}

// ボーン行列
cbuffer BoneBuffer : register(b6)
{
    column_major float4x4 BoneMatrices[128];
};