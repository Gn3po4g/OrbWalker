#include "pch.h"
#include <format>

void OrbWalker::Initialize() {
	renderer = (Renderer*)offsets.oViewProjMatrices;
	me = *(Object**)offsets.oLocalPlayer;
	heroes = *(ObjList**)offsets.oHeroList;
	attackables = *reinterpret_cast<ObjList**>(offsets.oAttackableList);
	//turrets = *(ObjList**)offsets.oTurretList;
	//inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(ObjList**)offsets.oMinionList;
	HUDInput = *(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x24);
	MousePos = (XMFLOAT3*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x14) + 0x1C);
}

void OrbWalker::AttackChampion() {
	const auto target = heroes->GetLowestHealth(me);
	if (target && Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(target->position);
		Functions::IssueOrder(HUDInput, 0, 1, 1, pos.x, pos.y, 0);
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
		Functions::GetGameTime() >= lastMoveTime + 50) {
		lastMoveTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(*MousePos);
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
	}
}

void OrbWalker::CleanLane() {
	const auto attackbale = attackables->GetLowestHealth(me);
	if (attackbale && Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(attackbale->position);
		Functions::IssueOrder(HUDInput, 0, 1, 1, pos.x, pos.y, 1);
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
		Functions::GetGameTime() >= lastMoveTime + 50) {
		const auto pos = renderer->WorldToScreen(*MousePos);
		lastMoveTime = Functions::GetGameTime();
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
	}
}
void OrbWalker::LastHit() {
	const auto target = minions->GetLastHit(me);
	if (target && Functions::GetGameTime() >= lastAttackTime + me->GetAD()) {
		lastAttackTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(target->position);
		Functions::IssueOrder(HUDInput, 0, 1, 1, pos.x, pos.y, 0);
	} else if (Functions::GetGameTime() >= lastAttackTime + me->GetACD() &&
		Functions::GetGameTime() >= lastMoveTime + 50) {
		lastMoveTime = Functions::GetGameTime();
		const auto pos = renderer->WorldToScreen(*MousePos);
		Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
	}
}
