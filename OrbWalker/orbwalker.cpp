module;
#include <Windows.h>
#include <chrono>
module OrbWalker;
import Object;
import Function;
import Offset;

using namespace std::chrono;

Object* me{};
ObjList* heroes{};
ObjList* minions{};
ObjList* turrets{};
//ObjList* inhibitors{};
uintptr_t hud_input{};

void InitOrb() {
	InitOffest();
	InitFunction();
	me = *(Object**)offset.oLocalPlayer;
	heroes = *(ObjList**)offset.oHeroList;
	turrets = *(ObjList**)offset.oTurretList;
	//inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(ObjList**)offset.oMinionList;
	hud_input = *(uintptr_t*)(*(uintptr_t*)offset.oHudInstance + 0x48);
	p_aco = (bool*)(*(uintptr_t*)(*(uintptr_t*)offset.oHudInstance + 0x60) + 0x30);
	while (*(float*)offset.oGameTime < .5f) std::this_thread::sleep_for(250ms);
	PrintChat(offset.oChatClient, "Noroby's League of Legends OrbWalker", 0xFF);
}

Object* GetTarget(const Type type) {
	Object* target = nullptr;
	if (type == Type::AutoKite) {
		target = heroes->GetLowestHealth(me, false);
	}
	if (type == Type::CleanLane) {
		target = minions->GetLowestHealth(me, true);
		if (target == nullptr) {
			target = turrets->GetLowestHealth(me, false);
		}
	}
	return target;
}

void Attack(Object* obj) {
	const auto pos = WorldToScreen(obj->position());
	IssueOrder(hud_input, 0, 0, 1, pos.x, pos.y, 0);
}

void Move() {
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

struct Timer {
	duration<float> last_attack_time{};
	duration<float> next_move_time{};
	duration<float> next_action_time{};
} timer;

void Execute(Type type) {
	const auto now = duration<float>(*(float*)offset.oGameTime);
	if (IsChatOpen() || IsLeagueInBackground() || now < timer.next_action_time) return;
	timer.next_action_time = now + milliseconds(33);
	if (const auto target = GetTarget(type); target  
		&& now >= timer.last_attack_time + me->ad()) {
		timer.last_attack_time = now;
		timer.next_move_time = now + me->acd();
		last_object = target;
		Attack(target);
	}
	else if (now >= timer.next_move_time) Move();
}

