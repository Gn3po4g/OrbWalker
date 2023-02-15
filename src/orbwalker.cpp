#include "pch.h"

Renderer* OrbWalker::renderer{};
Object* OrbWalker::me{};
HeroList* OrbWalker::heroes{};
ObjList* OrbWalker::turrets{};
ObjList* OrbWalker::inhibitors{};
MinionList* OrbWalker::minions{};
DWORD_PTR OrbWalker::HUDInput{};
XMFLOAT3* OrbWalker::MousePos{};
ULONGLONG OrbWalker::lastAttackTime{};

void OrbWalker::Initialize() {
	renderer = (Renderer*)offsets.oViewProjMatrices;
	me = *(Object**)offsets.oLocalPlayer;
	heroes = *(HeroList**)offsets.oHeroList;
	turrets = *(ObjList**)offsets.oTurretList;
	inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(MinionList**)offsets.oMinionList;
	HUDInput = *(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x24);
	MousePos = (XMFLOAT3*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x14) + 0x1C);
	Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
}

Object* OrbWalker::FindTarget(const Type& type) {
	switch (type) {
	case space: return heroes->GetLowestHealth(me);
	case v: return minions->GetLowestHealth(me);
	case x: return minions->GetLastHit(me);
	default: return nullptr;
	}
}

void OrbWalker::AttackObject(const Type& type) {
	if (Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		if (const auto target = FindTarget(type); target) {
			lastAttackTime = Functions::GetGameTime();
			const auto pos = renderer->WorldToScreen(target->position);
			Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 0);
			Functions::IssueOrder(HUDInput, 1, 1, 0, pos.x, pos.y, 0);
		} else {
			const auto pos = renderer->WorldToScreen(*MousePos);
			Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
			Functions::IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
		}
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD()) {
		const auto pos = renderer->WorldToScreen(*MousePos);
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
	}
}
