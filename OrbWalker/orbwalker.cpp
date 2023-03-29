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
		me = *(Object**)(Offsets::oLocalPlayer);
		heroes = *(ObjList**)(Offsets::oHeroList);
		//        attackables = *reinterpret_cast<ObjList**>(Offsets::oAttackableList);
		turrets = *(ObjList**)(Offsets::oTurretList);
		//inhibitors = *(ObjList**)Offsets::oInhibitorList;
		minions = *(ObjList**)(Offsets::oMinionList);
		HUDInput = *(uintptr_t*)(*(uintptr_t*)Offsets::oHudInstance + 0x24);
		MousePos = (XMFLOAT3*)(*(uintptr_t*)(*(uintptr_t*)Offsets::oHudInstance + 0x14) + 0x1C);
		pAttackChampionsOnly = (bool*)(*(::uintptr_t*)(*(::uintptr_t*)Offsets::oHudInstance + 0x30) + 0x20);
		Functions::GetGameTime();
	}

	Object* GetTarget(Type type) {
		switch (type) {
		case Type::AutoKite:
			return heroes->GetLowestHealth(me);
		case Type::CleanLane: {
			auto target = minions->GetLowestHealth(me);
			if (!target) target = turrets->GetLowestHealth(me);
			return target;
		}
		case Type::LastHit:
			return minions->GetLastHit(me);
		default:
			return nullptr;
		}
	}

	void Execute(Type type) {
		static uint64_t lastAttackTime{};
		static uint64_t lastActTime{};
		static uint64_t lastMoveTime{};
		static bool isTurningAround = false;
		if (Functions::GetGameTime() < lastActTime + 20) return;
		lastActTime = Functions::GetGameTime();
		if (auto target = GetTarget(type); target && (Functions::GetGameTime() >= lastAttackTime + me->GetAD() || isTurningAround)) {
			if (!isTurningAround) lastAttackTime = Functions::GetGameTime();
			isTurningAround = true;
			const auto pos = Renderer::WorldToScreen(target->position);
			Functions::IssueOrder(HUDInput, 0, 1, 0, pos.x, pos.y, 1);
			if (me->IsFacing(target)) {
				isTurningAround = false;
				lastMoveTime = Functions::GetGameTime() + me->GetACD();
			}
		} else if (Functions::GetGameTime() >= lastMoveTime) {
			const auto pos = Renderer::WorldToScreen(*MousePos);
			Functions::IssueOrder(HUDInput, 0, 0, 0, pos.x, pos.y, 0);
		}
	}
}