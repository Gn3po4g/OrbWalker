#include "pch.h"

float Object::DistanceTo(const Object* other) const {
	float dx = position.x - other->position.x;
	float dy = position.y - other->position.y;
	float dz = position.z - other->position.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

UINT Object::GetACD() const {
	return (UINT)(Functions::GetAttackCastDelay(this) * 1000) + 50;
}

UINT Object::GetAD() const {
	return (UINT)(Functions::GetAttackDelay(this) * 1000) + 10;
}
