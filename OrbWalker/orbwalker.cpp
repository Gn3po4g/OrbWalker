#include "pch.h"

OrbWalker::OrbWalker() {
	me = std::unique_ptr<Object>(GetLocalPlayer());
	heroes = std::unique_ptr<ObjList>(GetHeroList());
	turrets = std::unique_ptr<ObjList>(GetTurretList());
	inhibitors = std::unique_ptr<ObjList>(GetInhibitorList());
	minions = std::unique_ptr<ObjList>(GetMinionList());
}

void OrbWalker::AttackObject(const bool findHero) {
	if (!IsLeagueInForeground())return;
	Object* target = FindTarget(findHero);
	if (target && GetGameTimeTicks() > lastAttackTime + me->GetAttackDelayTicks()) {
		functions->IssueOrder(me.get(), 3, &target->position, target, false, false, 0);
		lastAttackTime = GetGameTimeTicks();
	} else if (GetGameTimeTicks() > lastMoveTime && GetGameTimeTicks() > lastAttackTime + me->GetAttackCastDelayTicks()) {
		auto p = GetMouseWorldPosition();
		functions->IssueOrder(me.get(), 2, &p, nullptr, false, false, 0);
		lastMoveTime = GetGameTimeTicks() + 30;
	}
}


Object* OrbWalker::FindTarget(const bool findHero) const {
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
		if (list->list[i]->DisTo(me.get()) > me->attackRange) continue;
		if (list->list[i]->team == me->team) continue;
		if (!list->list[i]->IsAlive()) continue;
		if (!list->list[i]->visible) continue;
		if (!list->list[i]->targetable) continue;
		if (!ret || list->list[i]->DisTo(me.get()) < ret->DisTo(me.get())) ret = list->list[i];
	}
	return ret;
}

std::unique_ptr<OrbWalker> orbWalker;
