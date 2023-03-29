#include "pch.h"

float Object::DistanceTo(Object* other) const {
	float dx = position.x - other->position.x;
	float dy = position.y - other->position.y;
	float dz = position.z - other->position.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

bool Object::IsFacing(Object* other) const {
	auto v1 = XMVector3Normalize(XMLoadFloat3(new XMFLOAT3(other->position.x - position.x, 0.f, other->position.z - position.z)));
	auto v2 = XMVector3Normalize(XMLoadFloat3(&direction));
	return XMConvertToDegrees(XMVectorGetX(XMVector3AngleBetweenVectors(v1, v2))) < 90.f;
}

double Object::GetBR() const {
	return Functions::GetRadius(this) - 1.0;
}

uint32_t Object::GetACD() const {
	return static_cast<uint32_t>(Functions::GetAttackCastDelay(this) * 1000) + 10;
}

uint32_t Object::GetAD() const {
	return static_cast<uint32_t>(Functions::GetAttackDelay(this) * 1000) + 10;
}
