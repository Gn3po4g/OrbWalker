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
ULONGLONG OrbWalker::lastMoveTime{};

void OrbWalker::Initialize() {
	renderer = (Renderer*)offsets.oViewProjMatrices;
	me = *(Object**)offsets.oLocalPlayer;
	heroes = *(HeroList**)offsets.oHeroList;
	turrets = *(ObjList**)offsets.oTurretList;
	inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(MinionList**)offsets.oMinionList;
	HUDInput = *(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x24);
	MousePos = (XMFLOAT3*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x14) + 0x1C);
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
	if (auto target = FindTarget(type); target &&
		Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(target->position);
		Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 1, 0, pos.x, pos.y, 0);
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
		Functions::GetGameTime() >= lastMoveTime + 50) {
		lastMoveTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(*MousePos);
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
	}
}
