#include "pch.h"

XMINT2 Renderer::WorldToScreen(const XMFLOAT3& pos) const {
	XMVECTOR ret = XMVector3TransformCoord(XMLoadFloat3(&pos), viewMatrix * projMatrix);
	return { (int)(.5f * width + .5f * width * XMVectorGetX(ret)),
					 (int)(.5f * height - .5f * height * XMVectorGetY(ret)) };
}
