#include "pch.h"

Object* HeroList::GetLowestHealth(const Object* obj) const {
	Object* ret = nullptr;
	vector<Object*> vec(list, list + size);
	for (auto o : vec) {
		if (Functions::IsAlive(o)
			&& o->team != obj->team && o->visible && o->targetable
			&& o->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(o)
			&& (!ret || o->health < ret->health)) {
			ret = o;
		}
	}
	return ret;
}

Object* MinionList::GetLowestHealth(const Object* obj) const {
	Object* ret = nullptr;
	vector<Object*> vec(list, list + size);
	for (auto o : vec) {
		if (Functions::IsAlive(o)
			&& o->team != obj->team && o->visible && o->targetable
			&& o->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(o)
			&& (!ret || o->health < ret->health)) {
			ret = o;
		}
	}
	return ret;
}

Object* MinionList::GetLastHit(const Object* obj) const {
	Object* ret = nullptr;
	vector<Object*> vec(list, list + size);
	for (auto o : vec) {
		if (Functions::IsAlive(o)
			&& o->health <= obj->base_attack + obj->bonus_attack
			&& o->team != obj->team && o->visible && o->targetable
			&& o->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(o)
			&& (!ret || o->health < ret->health)) {
			ret = o;
		}
	}
	return ret;
}