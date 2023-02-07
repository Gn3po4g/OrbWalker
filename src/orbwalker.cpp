#include "pch.h"
#include <format>

extern std::unique_ptr<Functions> f;

OrbWalker::OrbWalker() :
	renderer{ (Renderer*)offsets.oViewProjMatrices },
	me{ *(Object**)offsets.oLocalPlayer },
	heroes{ *(ObjList**)offsets.oHeroList },
	turrets{ *(ObjList**)offsets.oTurretList },
	inhibitors{ *(ObjList**)offsets.oInhibitorList },
	minions{ *(ObjList**)offsets.oMinionList } {
	f->PrintChat((PDWORD)offsets.oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
}

Object* OrbWalker::FindTarget(const bool& findHero) {
	if(findHero) return heroes->GetBestTargetFor(me);
	Object* target = turrets->GetBestTargetFor(me);
	if(!target) target = inhibitors->GetBestTargetFor(me);
	if(!target) target = minions->GetBestTargetFor(me);
	return target;
}

void OrbWalker::AttackObject(const bool& findHero) {
	if(const Object* target = FindTarget(findHero); target &&
		f->GetGameTime() >= lastAttackTime + f->GetAttackDelay(me) + .015f) {
		f->Attack(renderer->WorldToScreen(target->position));
		lastAttackTime = f->GetGameTime();
	} else if(f->GetGameTime() > lastMoveTime + .03f &&
		f->GetGameTime() >= lastAttackTime + f->GetAttackCastDelay(me) + .025f) {
		f->Click(renderer->WorldToScreen(f->GetMouseWorldPosition()));
		lastMoveTime = f->GetGameTime();
	}
}
