#include "pch.h"

Object* HeroList::GetLowestHealth(const Object* obj) const {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		if (Functions::IsAlive(list[i])
			&& list[i]->team != obj->team && list[i]->visible && list[i]->targetable
			&& list[i]->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(obj)
			&& (!ret || list[i]->health < ret->health)) {
			ret = list[i];
		}
	}
	return ret;
}

Object* MinionList::GetLowestHealth(const Object* obj) const {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		if (Functions::IsAlive(list[i])
			&& list[i]->team != obj->team && list[i]->visible && list[i]->targetable
			&& list[i]->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(obj)
			&& (!ret || list[i]->health < ret->health)) {
			ret = list[i];
		}
	}
	return ret;
}

Object* MinionList::GetLastHit(const Object* obj) const {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		if (Functions::IsAlive(list[i])
			&& list[i]->health <= obj->base_attack + obj->bonus_attack
			&& list[i]->team != obj->team && list[i]->visible && list[i]->targetable
			&& list[i]->DistanceTo(obj) <= obj->attack_range + Functions::GetRadius(obj)
			&& (!ret || list[i]->health < ret->health)) {
			ret = list[i];
		}
	}
	return ret;
}