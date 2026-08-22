/*============================================================
*	@file	 : MeshTypes.cpp
*	@brief	 : メッシュタイプ管理
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/07/26
*	@updated : 2026/08/04
*============================================================*/
#include "MeshTypes.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace DirectX;

/*--------------------------------------------------
    定数・構造体定義
----------------------------------------------------*/
namespace {

    // 標準となる頂点座標を定義
    constexpr std::array<Vector3, 4> BASE_VERTEX
    {
        Vector3{ -0.5f,  0.5f, 0.0f },
        Vector3{  0.5f,  0.5f, 0.0f },
        Vector3{ -0.5f, -0.5f, 0.0f },
        Vector3{  0.5f, -0.5f, 0.0f }
    };

    // UV座標定義
    constexpr std::array<Vector2, 4> UV
    {
        Vector2{ 0.0f, 0.0f },
        Vector2{ 1.0f, 0.0f },
        Vector2{ 0.0f, 1.0f },
        Vector2{ 1.0f, 1.0f }
    };

    // 向き情報構造体
    struct AXIS
    {
        // 代入軸情報
        uint8_t x;
        uint8_t y;
        uint8_t z;

        Vector3 normal; // 法線
    };

    // ピボット座標テーブル
    inline constexpr std::array<Vector2, static_cast<size_t>(MeshType::Plane::Pivot::Count)> OFFSET_TABLE
    {
                // X      Y 
        Vector2{  0.0f,  0.0f }, // 0.Center
        Vector2{  0.0f, -0.5f }, // 1.CenterTop
        Vector2{  0.0f,  0.5f }, // 2.CenterBottom
        Vector2{  0.5f, -0.5f }, // 3.LeftTop
        Vector2{  0.5f,  0.5f }, // 4.LeftBottom
        Vector2{ -0.5f, -0.5f }, // 5.RightTop
        Vector2{ -0.5f,  0.5f }  // 6.RightBottom
    };

    // 向き情報テーブル
    inline constexpr std::array<AXIS, static_cast<size_t>(MeshType::Plane::Axis::Count)> AXIS_TABLE
    {
        //    X  Y  Z                   法線
        AXIS{ 0, 1, 2 , Vector3{  0.0f, 0.0f ,1.0f }}, // 0.XY
        AXIS{ 0, 2, 1 , Vector3{  0.0f, 1.0f ,0.0f }}, // 1/XZ
        AXIS{ 1, 2, 0 , Vector3{  1.0f, 0.0f ,0.0f }}  // 2.YZ
    };

    /*--------------------------------------------------
        向き変換
    ----------------------------------------------------*/
    Vector3 ConvertAxis(const Vector3& position, const AXIS& axisInfo)
    {
        Vector3 newPosition{};

        std::array <float, 3>v{};

        // 座標代入
        v[axisInfo.x] = position.x;
        v[axisInfo.y] = position.y;
        v[axisInfo.z] = position.z;

        newPosition = { v[0], v[1], v[2] };

        return newPosition;
    }

    /*--------------------------------------------------
        頂点生成
    ----------------------------------------------------*/
    Element::VERTEX3D CreateVertex(size_t index, const MeshType::Plane::DESC& desc)
    {
        Element::VERTEX3D vertex{};

        // 基準座標で初期化
        Vector3 position = BASE_VERTEX[index];

        // ピボット補正
        const Vector2 offset = OFFSET_TABLE[static_cast<size_t>(desc.pivot)];
        Vector2 pos = { position.x, position.y };
        pos += offset;
        position = { pos.x, pos.y, position.z };

        // 向きを変換
        position = ConvertAxis(position, AXIS_TABLE[static_cast<size_t>(desc.axis)]);

        vertex.Position = position.ConvertToXMFLOAT3();
        vertex.Normal = AXIS_TABLE[static_cast<size_t>(desc.axis)].normal.ConvertToXMFLOAT3();
        vertex.Diffuse = XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
        vertex.TexCoord = UV[index].ConvertToXMFLOAT2();

        return vertex;
    }
}

std::array<Element::VERTEX3D, 4> MeshType::Plane::Create(const DESC& desc)
{
    std::array<Element::VERTEX3D, 4> vertices{};

    for (size_t i = 0; i < vertices.size(); ++i) {
        vertices[i] = CreateVertex(i, desc);
    }

    return vertices;
}
