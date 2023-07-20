module Object;

import Function;

duration<float> Object::acd() {
	auto origin = AttackCastDelay(this);
	return duration<float>(fmin(origin * 1.25f, origin + 0.05f));
}

duration<float> Object::ad() {
	return duration<float>(AttackDelay(this) + 0.015f);
}

bool Object::AttackableFor(Object *other) {
	return team != other->team && visible && targetable && IsAlive(this);
}

bool Object::InRangeOf(Object *other) {
	float dx = position.x - other->position.x;
	float dy = position.y - other->position.y;
	float dz = position.z - other->position.z;
	return sqrtf(dx * dx + dy * dy + dz * dz) <=
	       other->attackrange + BonusRadius(this) + BonusRadius(other);
}

using namespace std;

auto dif_cmp = [](Object *o, Object *smallest) {
	return o->health < smallest->health && o != last_object || smallest == last_object;
};

Object *ObjList::GetLowestHealth(Object *me, bool diff) {
	auto filtered = span(list, size) |
	                views::filter([me](Object *obj) {
		                return obj->AttackableFor(me) && obj->InRangeOf(me);
	                });
	auto num = ranges::distance(filtered);
	if (num == 0) return nullptr;
	else if (num == 1) return filtered.front();
	else return diff ? *ranges::min_element(filtered, dif_cmp) : *ranges::min_element(filtered);
}