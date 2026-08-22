/*------------------------------------------------------------
	ライトなし頂点シェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    Out = (PS_IN) 0;
    
    // ボーンウェイト取得
    float weight =
        In.BoneWeights.x +
        In.BoneWeights.y +
        In.BoneWeights.z +
        In.BoneWeights.w;
    
    float4 skinnedPosition = float4(0.0f, 0.0f, 0.0f, 0.0f);

    // スキニング行列適用
    if (weight > 0.0f)
    {
        skinnedPosition += mul(BoneMatrices[In.BoneIndices.x], In.Position) * In.BoneWeights.x;
        skinnedPosition += mul(BoneMatrices[In.BoneIndices.y], In.Position) * In.BoneWeights.y;
        skinnedPosition += mul(BoneMatrices[In.BoneIndices.z], In.Position) * In.BoneWeights.z;
        skinnedPosition += mul(BoneMatrices[In.BoneIndices.w], In.Position) * In.BoneWeights.w;
    }
    else
    {
        skinnedPosition = In.Position;
    }

    matrix wvp = mul(World, View);
    wvp = mul(wvp, Projection);

    Out.Position = mul(skinnedPosition, wvp);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}