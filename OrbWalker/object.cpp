#include "stdafx.hpp"

using namespace offset;

int Object::team() {
	return prop<int>(0x3C);
}

bool Object::visible() {
	return prop<bool>(0x310);
}

bool Object::targetable() {
	return prop<bool>(0xEB0);
}

float Object::attackrange() {
	return prop<float>(0x16B4);
}

FLOAT3 Object::position() {
	return prop<FLOAT3>(0x220);
}

float Object::health() {
	return prop<float>(0x1058);
}

float Object::height() {
	const auto characterHeight = *(float*)(*(uintptr_t*)(*(uintptr_t*)((uintptr_t)this + 0x3528) + 0x28) + 0xC4);
	const auto scale = *(float*)((uintptr_t)this + 0x1684);
	return characterHeight * scale;
}

float Object::AttackDelay() {
	using fnAttackDelay = float(__fastcall*)(Object*);
	return ((fnAttackDelay)oAttackDelay)(this);
}

float Object::AttackWindup() {
	using fnAttackWindup = float(__fastcall*)(Object*);
	return ((fnAttackWindup)oAttackWindup)(this);
}

bool Object::IsAlive() {
	using fnIsAlive = bool(__fastcall*)(Object*);
	return ((fnIsAlive)oIsAlive)(this);
}

bool Object::AttackableFor(Object* other) {
	return team() != other->team() &&
		visible() && targetable() && IsAlive();
}

bool Object::InRangeOf(Object* other) {
	using fnBonusRadius = float(__fastcall*)(Object*);
	const float dx = position().x - other->position().x;
	const float dy = position().y - other->position().y;
	const float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz) + 2.f < other->attackrange() +
		((fnBonusRadius)oBonusRadius)(this) + ((fnBonusRadius)oBonusRadius)(other);
}

Object** ObjList::list() {
	return prop<Object**>(0x8);
}

int ObjList::size() {
	return prop<int>(0x10);
}

Object* last_object = nullptr;

Object* ObjList::GetLowestHealth(bool diff) {
	Object* me = script::LocalPlayer();
	using namespace std;
	auto dif_cmp = [](Object* o, Object* smallest) {
		return o->health() < smallest->health() && o != last_object || smallest == last_object;
		};
	auto filtered = span(list(), size()) |
		views::filter([me](Object* obj) {
		return obj->AttackableFor(me) && obj->InRangeOf(me);
			});
	auto num = ranges::distance(filtered);
	if (num == 0) return nullptr;
	if (num == 1) return filtered.front();
	return diff ? *ranges::min_element(filtered, dif_cmp) : *ranges::min_element(filtered);
}
