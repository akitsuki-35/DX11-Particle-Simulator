/*------------------------------------------------------------
	ディレクショナルライト頂点シェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    Out = (PS_IN) 0;
    
    matrix wvp = mul(World, View); // World * View
    wvp = mul(wvp, Projection); // wvp * Projection
    Out.Position = mul(In.Position, wvp); // 頂点座標を行列で変換して出力
    
    // 法線の回転
    float4 worldNormal, normal;
    
    normal = float4(In.Normal.xyz, 0.0f); // 法線ベクトルの平行移動成分を0にする
    worldNormal = mul(normal, World); // 法線をワールド行列で回転
    worldNormal = normalize(worldNormal); // 回転後の法線を正規化
    Out.Normal = worldNormal; // 回転後の法線を出力

    // 光源計算
    // 光ベクトルと法線の内積計算
    //float light = -dot(Light.Direction.xyz, worldNormal.xyz); // xyz成分のみで計算
    float light = 0.5 - 0.5 * dot(Light.Direction.xyz, worldNormal.xyz); // ハーフランバート
    light = saturate(light); // 0.0～1.0に収める
    
    // 出力
    Out.Diffuse.rgb = light * Material.Diffuse.rgb + Light.Diffuse.rgb; // 明るさを頂点カラーとして出力
    Out.Diffuse.a = In.Diffuse.a; // 元の頂点のアルファ値のまま出力
    Out.TexCoord = In.TexCoord; // テクスチャ座標を出力
}