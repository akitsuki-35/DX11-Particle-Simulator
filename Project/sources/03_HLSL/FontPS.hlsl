/*------------------------------------------------------------
	フォントアトラス用ピクセルシェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

Texture2D		gTexture : register(t0);
SamplerState	gSamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    outDiffuse.rgb = In.Diffuse.rgb;
    
    float alpha = gTexture.Sample(gSamplerState, In.TexCoord).a;
    outDiffuse.a = In.Diffuse.a * alpha;
}
