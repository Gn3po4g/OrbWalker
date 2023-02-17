#include "pch.h"

Object* HeroList::GetLowestHealth(const Object* me) {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		Object* obj = *(list + i);
		if (Functions::IsAlive(obj) && obj->team != me->team && obj->visible && obj->targetable
			&& obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR()
			&& (!ret || obj->health < ret->health)) {
			ret = obj;
		}
	}
	return ret;
}

Object* MinionList::GetLowestHealth(const Object* me) {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		Object* obj = *(list + i);
		if (Functions::IsAlive(obj) && obj->team != me->team && obj->visible && obj->targetable
			&& obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR()
			&& (!ret || obj->health < ret->health)) {
			ret = obj;
		}
	}
	return ret;
}

Object* MinionList::GetLastHit(const Object* me) {
	Object* ret = nullptr;
	for (int i = 0; i < size; i++) {
		Object* obj = *(list + i);
		if (Functions::IsAlive(obj)
			&& obj->health <= me->base_attack + me->bonus_attack
			&& obj->team != me->team && obj->visible && obj->targetable
			&& obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR()
			&& (!ret || obj->health < ret->health)) {
			ret = obj;
		}
	}
	return ret;
}