#include "pch.h"

Renderer* OrbWalker::renderer{};
Object* OrbWalker::me{};
ObjList* OrbWalker::heroes{};
ObjList* OrbWalker::turrets{};
ObjList* OrbWalker::inhibitors{};
ObjList* OrbWalker::minions{};
DWORD_PTR OrbWalker::HUDInput{};
XMFLOAT3* OrbWalker::MousePos{};
ULONGLONG OrbWalker::lastAttackTime{};

void OrbWalker::Initialize() {
	renderer = (Renderer*)offsets.oViewProjMatrices;
	me = *(Object**)offsets.oLocalPlayer;
	heroes = *(ObjList**)offsets.oHeroList;
	turrets = *(ObjList**)offsets.oTurretList;
	inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(ObjList**)offsets.oMinionList;
	HUDInput = *(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x24);
	MousePos = (XMFLOAT3*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x14) + 0x1C);
	Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
}

Object* OrbWalker::FindTarget(const bool& findHero) {
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
		Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 1, 0, pos.x, pos.y, 0);
	} else if(GetTickCount64() >= lastAttackTime + me->GetACD()) {
		const auto pos = renderer->WorldToScreen(*MousePos);
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
	}
}
