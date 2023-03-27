#include "pch.h"

namespace Renderer {
    XMFLOAT4X4 *view_matrix;
    XMFLOAT4X4 *proj_matrix;
    int *width;
    int *height;

    void Initialize() {
        view_matrix = (XMFLOAT4X4 *) (Offsets::oViewProjMatrices + 0x00);
        proj_matrix = (XMFLOAT4X4 *) (Offsets::oViewProjMatrices + 0x40);
        width = (int *) (Offsets::oViewProjMatrices + 0x94);
        height = (int *) (Offsets::oViewProjMatrices + 0x98);
    }

    XMINT2 WorldToScreen(const XMFLOAT3 &pos) {
        FXMVECTOR V = XMVectorSetW(XMLoadFloat3(&pos), 1.f);
        FXMMATRIX M = XMLoadFloat4x4(view_matrix) * XMLoadFloat4x4(proj_matrix);
        FXMVECTOR coord = XMVector3TransformCoord(V, M);
        const auto w = (float) *width, h = (float) *height;
        return {(int) (.5f * w + .5f * w * XMVectorGetX(coord)),
                (int) (.5f * h - .5f * h * XMVectorGetY(coord))};
    }
}