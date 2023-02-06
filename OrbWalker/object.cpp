#include "pch.h"

using namespace DirectX;

float Object::operator-(const Object& other) const {
	XMVECTOR v1 = XMLoadFloat3(&position);
	XMVECTOR v2 = XMLoadFloat3(&other.position);
	XMVECTOR vectorSub = XMVectorSubtract(v1, v2);
	return XMVectorGetX(XMVector3Length(vectorSub));
}