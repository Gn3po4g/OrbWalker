#include "stdafx.hpp"

namespace script {
	Object* LocalPlayer() { return *(Object**)offset::oLocalPlayer; }
	ObjList* Heroes() { return *(ObjList**)offset::oHeroList; }
	ObjList* Minions() { return *(ObjList**)offset::oMinionList; }
	ObjList* Turrets() { return *(ObjList**)offset::oTurretList; }

	Object* GetTarget(const Type type) {
		Object* target = nullptr;
		if (type == Type::AutoKite) {
			target = Heroes()->GetLowestHealth(false);
		}
		else if (type == Type::CleanLane) {
			if (!(target = Minions()->GetLowestHealth(true)))
				target = Turrets()->GetLowestHealth(false);
		}
		return target;
	}

	void Execute(Type type) {
		static float last_attack_time{};
		static float last_move_time{};
		const auto self = LocalPlayer();
		if (!(self && self->IsAlive()) || IsChatOpen() || IsLeagueInBackground()) return;
		const auto now = GameTime();
		if (const auto target = GetTarget(type); target &&
			now > last_attack_time + self->AttackDelay() + 15e-3f) {
			last_attack_time = now;
			last_object = target;
			Attack(target);
		}
		else if (now > last_move_time + 33e-3f &&
			now > last_attack_time + self->AttackWindup() + 55e-3f) {
			last_move_time = now;
			Move2Mouse();
		}
	}
}