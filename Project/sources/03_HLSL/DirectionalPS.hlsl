/*------------------------------------------------------------
	ディレクショナルライトピクセルシェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

Texture2D gTexture : register(t0); // 0番テクスチャ
SamplerState gSamplerState : register(s0); // 0番サンプラー

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse = gTexture.Sample(gSamplerState, In.TexCoord); // テクスチャカラーを取得
    outDiffuse *= In.Diffuse; // 頂点の明るさを合成
}