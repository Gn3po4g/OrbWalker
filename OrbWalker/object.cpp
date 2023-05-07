#include "pch.h"

XMFLOAT3 Object::position() const {
	return *(XMFLOAT3*)((uintptr_t)this + 0x220);
}

bool Object::AttackableFor(Object* const other) const {
	return *(int32_t*)((uintptr_t)this + 0x3C) != *(int32_t*)((uintptr_t)other + 0x3C)
		&& *(bool*)((uintptr_t)this + 0x310) //visible
		&& *(bool*)((uintptr_t)this + 0xEB0) //targetable
		&& Functions::IsAlive(this);
}

float Object::health() const {
	return *(float*)((uintptr_t)this + 0x1058);
}

float Object::attack() const {
	return *(float*)((uintptr_t)this + 0x1654) + *(float*)((uintptr_t)this + 0x15C0);
}

bool Object::InRangeOf(Object* const other) const {
	float dx = position().x - other->position().x;
	float dy = position().y - other->position().y;
	float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz) 
		<= *(float*)((uintptr_t)other + 0x169C) //attack_range
		+ Functions::GetRadius(this) + Functions::GetRadius(other);
}

float Object::acd() const {
	return Functions::GetAttackCastDelay(this) / 8;
}

float Object::ad() const {
	return Functions::GetAttackDelay(this) + 0.01f;
}

bool Object::IsFacing(Object* const other) const {
	auto v1 = XMLoadFloat3(new XMFLOAT3(other->position().x - position().x, 0.f, other->position().z - position().z));
	auto v2 = XMLoadFloat3((XMFLOAT3*)((uintptr_t)this + 0x2190));
	return XMVectorGetX(XMVector3AngleBetweenVectors(v1, v2)) < 0.174533f;
}