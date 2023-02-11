#include "pch.h"

XMINT2 Renderer::WorldToScreen(const XMFLOAT3& pos) const {
	FXMVECTOR V = XMVectorSetW(XMLoadFloat3(&pos), 1.f);
	FXMMATRIX M = XMLoadFloat4x4(&view_matrix) * XMLoadFloat4x4(&proj_matrix);
	FXMVECTOR coord = XMVector3TransformCoord(V, M);
	return { (int)(.5f * width + .5f * width * XMVectorGetX(coord)),
					 (int)(.5f * height - .5f * height * XMVectorGetY(coord)) };
}
