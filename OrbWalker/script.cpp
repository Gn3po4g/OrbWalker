#include "stdafx.hpp"

namespace script {
	Object* LocalPlayer() { return *(Object**)offset::oLocalPlayer; }
	ObjList* Heroes() { return *(ObjList**)offset::oHeroList; }
	ObjList* Minions() { return *(ObjList**)offset::oMinionList; }
	ObjList* Turrets() { return *(ObjList**)offset::oTurretList; }

	Object* GetTarget(const Type type) {
		switch (type) {
		case Type::AutoKite:
			return Heroes()->GetLowestHealth(false);
		case Type::CleanLane:
			if (const auto target = Minions()->GetLowestHealth(true)) return target;
			else return Turrets()->GetLowestHealth(false);
		default:
			return nullptr;
		}
	}

	void Execute(Type type) {
		static float last_attack_time{};
		static float last_move_time{};
		const auto self = LocalPlayer();
		if (!(self && self->IsAlive()) || IsChatOpen() || IsLeagueInBackground()) return;
		const auto now = GameTime();
		if (const auto target = GetTarget(type); target &&
			std::is_gt(now <=> last_attack_time + self->AttackDelay() + 15e-3f)) {
			last_attack_time = now;
			last_object = target;
			Attack(target);
		}
		else if (std::is_gt(now <=> last_move_time + 33e-3f) &&
			std::is_gt(now <=> last_attack_time + self->AttackWindup() + 75e-3f)) {
			last_move_time = now;
			Move2Mouse();
		}
	}
}