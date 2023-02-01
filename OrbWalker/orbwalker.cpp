#include "pch.h"

OrbWalker::OrbWalker() {
	renderer = (Renderer*)oViewProjMatrices;
	me = *(Object**)oLocalPlayer;
	heroes = *(ObjList**)oHeroList;
	turrets = std::unique_ptr<ObjList>(*(ObjList**)oTurretList);
	inhibitors = std::unique_ptr<ObjList>(*(ObjList**)oInhibitorList);
	minions = std::unique_ptr<ObjList>(*(ObjList**)oMinionList);
}

void OrbWalker::AttackObject(bool findHero) {
	//if (!IsLeagueInForeground())return;
	Object* target = FindTarget(findHero);
	//Print(std::format("{},{}", p.x, p.y).c_str());
	if (target && GetTickCount64() >= lastAttackTime + me->GetAttackDelay() * 1000.f) {
		Attack(renderer->WorldToScreen(target->position));
		lastAttackTime = GetTickCount64();
	}
	else if (GetTickCount64() > lastMoveTime + 30 && GetTickCount64() >= lastAttackTime + me->GetAttackCastDelay() * 1000.f + 100) {
		Click(renderer->WorldToScreen(GetMouseWorldPosition()));
		lastMoveTime = GetTickCount64();
	}
}


Object* OrbWalker::FindTarget(bool findHero) const {
	if (findHero) return GetObjFromList(heroes);
	else {
		Object* target = GetObjFromList(turrets.get());
		if (!target) target = GetObjFromList(inhibitors.get());
		if (!target) target = GetObjFromList(minions.get());
		return target;
	}
}

Object* OrbWalker::GetObjFromList(const ObjList* list) const {
	Object* ret = nullptr;
	for (int i = 0; i < list->size; i++) {
		if (list->list[i]->team != me->team
			&& list->list[i]->IsAlive()
			&& list->list[i]->visible
			&& list->list[i]->targetable
			&& list->list[i]->DisTo(me) <= me->attackRange) {
			if (!ret) ret = list->list[i];
			else if (list->list[i]->DisTo(me) < ret->DisTo(me))ret = list->list[i];
		}
	}
	return ret;
}

std::unique_ptr<OrbWalker> orbWalker;
