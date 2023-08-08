#include "object.hpp"
#include "function.hpp"
#include "offset.hpp"
#include <span>
#include <ranges>

using namespace offset;

int Object::team() {
	return OFFSET(int, 0x3C);
}

bool Object::visible() {
	return OFFSET(bool, 0x310);
}

bool Object::targetable() {
	return OFFSET(bool, 0xEB0);
}

float Object::attackrange() {
	return OFFSET(float, 0x16B4);
}

DirectX::XMFLOAT3 Object::position() {
	return OFFSET(DirectX::XMFLOAT3, 0x220);
}

float Object::health() {
	return OFFSET(float, 0x1058);
}

float Object::AttackDelay() {
	using fnAttackDelay = float(__fastcall*)(Object*);
	return ((fnAttackDelay)oAttackDelay)(this);
}

float Object::AttackWindup() {
	using fnAttackWindup = float(__fastcall*)(Object*);
	return ((fnAttackWindup)oAttackWindup)(this);
}


bool Object::AttackableFor(Object* other) {
	using fnIsAlive = bool(__fastcall*)(Object*);
	return team() != other->team() &&
		visible() && targetable() &&
		((fnIsAlive)oIsAlive)(this);
}

bool Object::InRangeOf(Object* other) {
	using fnBonusRadius = float(__fastcall*)(Object*);
	const float dx = position().x - other->position().x;
	const float dy = position().y - other->position().y;
	const float dz = position().z - other->position().z;
	return sqrtf(dx * dx + dy * dy + dz * dz) + 2.f < other->attackrange() +
		((fnBonusRadius)oBonusRadius)(this) +
		((fnBonusRadius)oBonusRadius)(other);
}

Object** ObjList::list() {
	return OFFSET(Object**, 0x8);
}

int ObjList::size() {
	return OFFSET(int, 0x10);
}

Object* last_object = nullptr;

Object* ObjList::GetLowestHealth(Object* me, bool diff) {
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
