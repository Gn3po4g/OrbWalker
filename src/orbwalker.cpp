#include "pch.h"
#include <format>

extern std::unique_ptr<Functions> f;

OrbWalker::OrbWalker() :
	renderer((Renderer*)offsets.oViewProjMatrices),
	me(*(Object**)offsets.oLocalPlayer),
	heroes(*(ObjList**)offsets.oHeroList),
	turrets(*(ObjList**)offsets.oTurretList),
	inhibitors(*(ObjList**)offsets.oInhibitorList),
	minions(*(ObjList**)offsets.oMinionList),
	HUDInput(*(PDWORD)(*(PDWORD)offsets.oHudInstance + 0x24)),
	MousePos((XMFLOAT3*)(*(PDWORD)(*(PDWORD)offsets.oHudInstance + 0x14) + 0x1C)) {
	f->PrintChat((PDWORD)offsets.oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
}

Object* OrbWalker::FindTarget(const bool& findHero) const {
	if(findHero) return heroes->GetBestTargetFor(me);
	Object* target = turrets->GetBestTargetFor(me);
	if(!target) target = inhibitors->GetBestTargetFor(me);
	if(!target) target = minions->GetBestTargetFor(me);
	return target;
}

void OrbWalker::AttackObject(const bool& findHero) {
	if(const auto target = FindTarget(findHero); target &&
		GetTickCount64() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = GetTickCount64();
		const auto pos = renderer->WorldToScreen(target->position);
		f->IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 0);
		f->IssueOrder(HUDInput, 1, 1, 0, pos.x, pos.y, 0);
	} else if(GetTickCount64() >= lastAttackTime + me->GetACD()) {
		const auto pos = renderer->WorldToScreen(*MousePos);
		f->IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		f->IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
	}
}
