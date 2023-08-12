#include <Windows.h>
#include "object.hpp"
#include "function.hpp"
#include "offset.hpp"
#include "script.hpp"

namespace script {
	Object* me{};
	ObjList* heroes{};
	ObjList* minions{};
	ObjList* turrets{};

	void Init() {
		using namespace offset;
		me = *(Object**)oLocalPlayer;
		heroes = *(ObjList**)oHeroList;
		turrets = *(ObjList**)oTurretList;
		minions = *(ObjList**)oMinionList;
	}

	Object* GetTarget(const Type type)
	{
		Object* target = nullptr;
		if (type == Type::AutoKite) {
			target = heroes->GetLowestHealth(me, false);
		}
		else if (type == Type::CleanLane) {
			(target = minions->GetLowestHealth(me, true)) || (target = turrets->GetLowestHealth(me, false));
		}
		return target;
	}

	void Execute(Type type) {
		static float last_attack_time{};
		static float last_move_time{};
		if (!(me && me->IsAlive()) || IsChatOpen() || IsLeagueInBackground()) return;
		const auto now = GameTime();
		if (const auto target = GetTarget(type); target &&
			now > last_attack_time + me->AttackDelay() + 15e-3f) {
			last_attack_time = now;
			last_object = target;
			Attack(me, target);
		}
		else if (now > last_move_time + 33e-3f &&
			now > last_attack_time + me->AttackWindup() + 60e-3f) {
			last_move_time = now;
			Move2Mouse();
		}
	}
}