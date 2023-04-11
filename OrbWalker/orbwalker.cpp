#include "pch.h"

namespace OrbWalker {
	ObjList* turrets{};
	ObjList* inhibitors{};
	uintptr_t HUDInput{};
	XMFLOAT3* MousePos{};
	Object* me{};
	ObjList* heroes{};
	ObjList* minions{};
	ObjList* attackables{};
	bool* pAttackChampionsOnly;

	void Initialize() {
		me = *(Object**)(offsets.oLocalPlayer);
		heroes = *(ObjList**)(offsets.oHeroList);
		turrets = *(ObjList**)(offsets.oTurretList);
		////inhibitors = *(ObjList**)offsets.oInhibitorList;
		minions = *(ObjList**)(offsets.oMinionList);
		HUDInput = *(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x48);
		MousePos = (XMFLOAT3*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x28) + 0x20);
		pAttackChampionsOnly = (bool*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x60) + 0x30);
	}

	Object* GetTarget(Type type) {
		Object* target = nullptr;
		switch (type) {
		case Type::AutoKite:
			target = heroes->GetLowestHealth(me);
			break;
		case Type::CleanLane:
			(target = minions->GetLowestHealth(me)) || (target = turrets->GetLowestHealth(me));
			break;
		case Type::LastHit:
			target = minions->GetLastHit(me);
			break;
		default: break;
		}
		return target;
	}

	void Execute(Type type) {
		static uint64_t lastAttackTime{};
		static uint64_t lastActTime{};
		static uint64_t lastMoveTime{};
		static bool isTurningAround = false;
		if (Functions::GetGameTime() < lastActTime + 33) return;
		lastActTime = Functions::GetGameTime();
		if (auto target = GetTarget(type); target && (Functions::GetGameTime() >= lastAttackTime + me->AD() || isTurningAround)) {
			if (!isTurningAround) lastAttackTime = Functions::GetGameTime();
			isTurningAround = true;
			const auto pos = Renderer::WorldToScreen(target->position());
			Functions::IssueOrder(HUDInput, 0, 0, 1, pos.x, pos.y, 1);
			if (me->IsFacing(target)) {
				isTurningAround = false;
				lastMoveTime = Functions::GetGameTime() + me->ACD();
			}
		} else if (Functions::GetGameTime() >= lastMoveTime) {
			const auto pos = Renderer::WorldToScreen(*MousePos);
			Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		}
	}
}