#include "pch.h"

Object* ObjList::GetBestTargetFor(const Object* obj) const {
	extern std::unique_ptr<Functions> f;
	Object* ret = nullptr;
	for(int i = 0; i < size; i++) {
		if(f->IsAlive(list[i])
			&& list[i]->team != obj->team
			&& list[i]->visible
			&& list[i]->targetable
			&& list[i]->DistanceTo(obj) <= obj->attack_range + f->GetRadius(obj)
			&& (!ret || list[i]->health < ret->health)) {
			ret = list[i];
		}
	}
	return ret;
}
