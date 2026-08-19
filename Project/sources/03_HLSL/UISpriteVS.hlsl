/*------------------------------------------------------------
	2DUI用頂点シェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    Out = (PS_IN) 0;
    
    float4 pos = float4(In.Position.xyz, 1.0f);
    
    float4 world = mul(pos, World);
    float4 view = mul(View, world);
    
    Out.Position = mul(view, Projection);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;
}