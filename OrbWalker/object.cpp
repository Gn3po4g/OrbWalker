module;
#include <cmath>
#include <cstdint>
#include <span>
#include <ranges>
#include <vector>
module Object;
import Function;

XMFLOAT3 Object::position() const {
	return *(XMFLOAT3*)((uintptr_t)this + 0x220);
}

bool Object::AttackableFor(Object* const other) const {
	return *(int32_t*)((uintptr_t)this + 0x3C) != *(int32_t*)((uintptr_t)other + 0x3C) //team
		&& *(bool*)((uintptr_t)this + 0x310) //visible
		&& *(bool*)((uintptr_t)this + 0xEB0) //targetable
		&& IsAlive(this);
}

float Object::health() const {
	return *(float*)((uintptr_t)this + 0x1068);
}

bool Object::InRangeOf(Object* const other) const {
	float dx = position().x - other->position().x;
	float dy = position().y - other->position().y;
	float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz)
		<= *(float*)((uintptr_t)other + 0x16C4) //attack_range
		+ GetRadius(this) / 2 + GetRadius(other);
}

duration<float> Object::acd() const {
	return duration<float>(GetAttackCastDelay(this) * 1.1f);
}

duration<float> Object::ad() const {
	return duration<float>(GetAttackDelay(this) + 0.015f);
}

using namespace std;

auto dif_cmp = [](Object* o, Object* smallest) { return o->health() < smallest->health() && o != last_object || smallest == last_object; };

Object* ObjList::GetLowestHealth(Object* const me, const bool diff) const {
	auto filtered = span(*(Object***)((uintptr_t)this + 0x8), *(int*)((uintptr_t)this + 0x10))
		| views::filter([&](Object* obj) {return obj->AttackableFor(me) && obj->InRangeOf(me); });
	auto size = ranges::distance(filtered);
	if (size == 0) return nullptr;
	else if (size == 1) return filtered.front();
	else return diff ? *ranges::min_element(filtered, dif_cmp) : *ranges::min_element(filtered);
}