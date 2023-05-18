module;
#include <cmath>
#include <cstdint>
#include <span>
#include <ranges>
#include <vector>
module Object;
import Function;

XMFLOAT3 Object::position() {
	return *(XMFLOAT3*)((uintptr_t)this + 0x220);
}


float Object::health() {
	return *(float*)((uintptr_t)this + 0x1068);
}

duration<float> Object::acd() {
	return duration<float>(GetAttackCastDelay(this) * 1.1f);
}

duration<float> Object::ad() {
	return duration<float>(GetAttackDelay(this) + 0.015f);
}

bool Object::AttackableFor(Object* other) {
	return *(int32_t*)((uintptr_t)this + 0x3C) != *(int32_t*)((uintptr_t)other + 0x3C) //team
		&& *(bool*)((uintptr_t)this + 0x310) //visible
		&& *(bool*)((uintptr_t)this + 0xEB0) //targetable
		&& IsAlive(this);
}

bool Object::InRangeOf(Object* other) {
	float dx = position().x - other->position().x;
	float dy = position().y - other->position().y;
	float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz)
		<= *(float*)((uintptr_t)other + 0x16C4) //attack_range
		+ GetRadius(this) / 2 + GetRadius(other);
}

using namespace std;

auto dif_cmp = [](Object* o, Object* smallest) { return o->health() < smallest->health() && o != last_object || smallest == last_object; };

Object* ObjList::GetLowestHealth(Object* me, bool diff) {
	auto list = span(*(Object***)((uintptr_t)this + 0x8), *(int*)((uintptr_t)this + 0x10));
	auto filtered = list | views::filter([me](Object* obj) { return obj->AttackableFor(me) && obj->InRangeOf(me); });
	auto size = ranges::distance(filtered);
	if (size == 0) return nullptr;
	else if (size == 1) return filtered.front();
	else return diff ? *ranges::min_element(filtered, dif_cmp) : *ranges::min_element(filtered);
}