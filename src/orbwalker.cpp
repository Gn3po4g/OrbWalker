#include "pch.h"
#include <format>

Renderer* OrbWalker::renderer{};
Object* OrbWalker::me{};
ObjList* OrbWalker::heroes{};
ObjList* OrbWalker::turrets{};
ObjList* OrbWalker::inhibitors{};
ObjList* OrbWalker::minions{};
DWORD_PTR OrbWalker::HUDInput{};
XMFLOAT3* OrbWalker::MousePos{};
ULONGLONG OrbWalker::lastAttackTime{};
ULONGLONG OrbWalker::lastMoveTime{};

void OrbWalker::Initialize() {
	renderer = (Renderer*)offsets.oViewProjMatrices;
	me = *(Object**)offsets.oLocalPlayer;
	heroes = *(ObjList**)offsets.oHeroList;
	//turrets = *(ObjList**)offsets.oTurretList;
	//inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(ObjList**)offsets.oMinionList;
	HUDInput = *(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x24);
	MousePos = (XMFLOAT3*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x14) + 0x1C);
}

void OrbWalker::AttackChampion() {
	if (auto target = heroes->GetLowestHealth(me); target &&
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

void OrbWalker::CleanLane() {
	const auto pos = renderer->WorldToScreen(*MousePos);
	if (Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = Functions::GetGameTime();
		Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 1, 0, pos.x, pos.y, 0);
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
		Functions::GetGameTime() >= lastMoveTime + 50) {
		lastMoveTime = Functions::GetGameTime();
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		Functions::IssueOrder(HUDInput, 1, 0, 0, pos.x, pos.y, 0);
	}
}
void OrbWalker::LastHit() {
	if (auto target = minions->GetLastHit(me); target &&
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
