#include "pch.h"

using namespace std;

Object* ObjList::GetLowestHealth(Object* me) const {
	span<Object*> obj_list(*(Object***)((uintptr_t)this + 0x8), *(int*)((uintptr_t)this + 0x10));
	Object* current = nullptr;
	float min_health = FLT_MAX;
	for (auto obj : obj_list) {
		if (Functions::IsAlive(obj) && obj->team() != me->team() && obj->visible() && obj->targetable()
			&& obj->DistanceTo(me) <= me->attack_range() + obj->BR() + me->BR()) {
			if (obj->health() < min_health) {
				min_health = obj->health();
				current = obj;
			}
		}
	}
	return current;
}

Object* ObjList::GetLastHit(Object* me) const {
	span<Object*> obj_list(*(Object***)((uintptr_t)this + 0x8), *(int*)((uintptr_t)this + 0x10));
	for (auto obj : obj_list) {
		if (Functions::IsAlive(obj) && obj->team() != me->team() && obj->visible() && obj->targetable()
			&& obj->DistanceTo(me) <= me->attack_range() + obj->BR() + me->BR()) {
			if (obj->health() < me->base_attack() + me->bonus_attack()) {
				return obj;
			}
		}
	}
	return nullptr;
}