/*------------------------------------------------------------
	フォントアトラス用ピクセルシェーダー（アウトラインあり）
------------------------------------------------------------*/
#include "Common.hlsl"

Texture2D		gTexture : register(t0);
SamplerState	gSamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float width, height;
    gTexture.GetDimensions(width, height);
    float2 size = float2(1.0f / width, 1.0f / height);
    
    float alphaCenter = gTexture.Sample(gSamplerState, In.TexCoord).a;
    
    float alphaUp = gTexture.Sample(gSamplerState, In.TexCoord + float2(0.0f, -1.0f) * size).a;
    float alphaDown =  gTexture.Sample(gSamplerState, In.TexCoord + float2(0.0f, 1.0f) * size).a;
    float alphaLeft =  gTexture.Sample(gSamplerState, In.TexCoord + float2(-1.0f, 0.0f) * size).a;
    float alphaRight = gTexture.Sample(gSamplerState, In.TexCoord + float2(1.0f, 0.0f) * size).a;
    
    float maxAlphaAround = max(max(alphaUp, alphaDown), max(alphaLeft, alphaRight));
    float4 outlineColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    outDiffuse = lerp(outlineColor, In.Diffuse, alphaCenter);
    outDiffuse.a = max(alphaCenter, maxAlphaAround) * In.Diffuse.a;
}
