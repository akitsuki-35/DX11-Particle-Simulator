# Particle Simulator

DirectX11 DirectX11によるパーティクルシミュレーター<br>
開発環境：Visual Studio 2022 / 2026

- 三次ベジエ曲線上のパーティクル描画に対応
- ImGuiによる値の制御に対応

## ImGui Parameters
|Type|Name|Usage|
|--|--|--|
|Vector3|ControlPOINT[n]|制御点座標|
|int|Time|パーティクル全体フレーム|
|int|Count|1度あたりのパーティクル発射数|
|double|Interval|パーティクル発射間隔|
|float3|MainColor|パーティクルメインカラー|
|float3|MainColor|パーティクルサブカラー|

## Attention
Countを増やすほど、Intervalを減らすほどパーティクル発射数が増加するため、負荷が増加します。