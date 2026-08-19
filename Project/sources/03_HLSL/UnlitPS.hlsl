/*------------------------------------------------------------
	ライトなしピクセルシェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

Texture2D		gTexture : register(t0);
SamplerState	gSamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	if (Material.TextureEnable)
	{
		outDiffuse = gTexture.Sample(gSamplerState, In.TexCoord);
		outDiffuse *= In.Diffuse;
	}
	else
	{
		outDiffuse = In.Diffuse;
	}	
}
