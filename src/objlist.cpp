#include "pch.h"

Object* ObjList::GetBestTargetFor(const Object* obj) const {
	extern std::unique_ptr<Functions> f;
	Object* ret = nullptr;
	for(int i = 0; i < size; i++) {
		const auto cur = list[i];
		if(f->IsAlive(cur)
			&& cur->team != obj->team
			&& cur->visible
			&& cur->targetable
			&& *cur - *obj <= obj->attack_range + 25.f
			&& (!ret || cur->health < ret->health)) {
			ret = cur;
		}
	}
	return ret;
}
