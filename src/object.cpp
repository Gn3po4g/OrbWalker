#include "pch.h"

float Object::DistanceTo(const Object* other) const {
	float dx = position.x - other->position.x;
	float dy = position.y - other->position.y;
	float dz = position.z - other->position.z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}

UINT Object::GetACD() const {
	extern std::unique_ptr<Functions> f;
	return (UINT)(f->GetAttackCastDelay(this) * 1000) + 30;
}

UINT Object::GetAD() const {
	extern std::unique_ptr<Functions> f;
	return (UINT)(f->GetAttackDelay(this) * 1000) + 10;
}
