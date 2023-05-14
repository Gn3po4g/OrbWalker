#include "pch.h"

XMFLOAT3 Object::position() const {
	return *(XMFLOAT3*)((uintptr_t)this + 0x220);
}

bool Object::AttackableFor(Object* const other) const {
	return *(int32_t*)((uintptr_t)this + 0x3C) != *(int32_t*)((uintptr_t)other + 0x3C) //team
		&& *(bool*)((uintptr_t)this + 0x310) //visible
		&& *(bool*)((uintptr_t)this + 0xEB0) //targetable
		&& Functions::IsAlive(this);
}

float Object::health() const {
	return *(float*)((uintptr_t)this + 0x1058);
}

bool Object::InRangeOf(Object* const other) const {
	float dx = position().x - other->position().x;
	float dy = position().y - other->position().y;
	float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz)
		<= *(float*)((uintptr_t)other + 0x169C) //attack_range
		+ Functions::GetRadius(this) + Functions::GetRadius(other) - 5.f;
}

duration<float> Object::acd() const {
	return duration<float>(Functions::GetAttackCastDelay(this) * 1.1f);
}

duration<float> Object::ad() const {
	return duration<float>(Functions::GetAttackDelay(this) + 0.015f);
}