#include "pch.h"

OrbWalker::OrbWalker() {
	renderer = std::unique_ptr<Renderer>((Renderer*)oViewProjMatrices);
	me = std::unique_ptr<Object>(*(Object**)oLocalPlayer);
	heroes = std::unique_ptr<ObjList>(*(ObjList**)oHeroList);
	turrets = std::unique_ptr<ObjList>(*(ObjList**)oTurretList);
	inhibitors = std::unique_ptr<ObjList>(*(ObjList**)oInhibitorList);
	minions = std::unique_ptr<ObjList>(*(ObjList**)oMinionList);
}

void OrbWalker::AttackObject(bool findHero) {
	//if (!IsLeagueInForeground())return;
	Object* target = FindTarget(findHero);
	//Print(std::format("{:#x}", oHeroList).c_str());
	if (target && GetGameTime() > lastMoveTime && GetGameTime() > lastAttackTime + me->GetAttackDelay() + 0.03) {
		Attack(renderer->WorldToScreen(target->position));
		lastAttackTime = GetGameTime();
	}
	else if (GetGameTime() > lastMoveTime && GetGameTime() > lastAttackTime + me->GetAttackCastDelay() + 0.05) {
		Click(renderer->WorldToScreen(GetMouseWorldPosition()));
		lastMoveTime = GetGameTime() + 0.06f;
	}
}


Object* OrbWalker::FindTarget(bool findHero) const {
	Object* target;
	if (findHero)target = GetObjFromList(heroes.get());
	else {
		target = GetObjFromList(turrets.get());
		if (!target) target = GetObjFromList(inhibitors.get());
		if (!target) target = GetObjFromList(minions.get());
	}
	return target;
}

Object* OrbWalker::GetObjFromList(const ObjList* list) const {
	Object* ret = nullptr;
	for (int i = 0; i < list->size; i++) {
		if (!list->list[i]->IsAlive()) continue;
		if (!list->list[i]->visible) continue;
		if (!list->list[i]->targetable) continue;
		if (list->list[i]->team == me->team) continue;
		if (list->list[i]->DisTo(me.get()) > me->attackRange) continue;
		if (!ret || list->list[i]->DisTo(me.get()) < ret->DisTo(me.get())) ret = list->list[i];
	}
	return ret;
}

std::unique_ptr<OrbWalker> orbWalker;
