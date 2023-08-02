#include <chrono>
#include <Windows.h>
#include "object.hpp"
#include "function.hpp"
#include "offset.hpp"
#include "orbwalker.hpp"

bool* p_aco = nullptr;

Object* me{};
ObjList* heroes{};
ObjList* minions{};
ObjList* turrets{};
//ObjList* inhibitors{};
uintptr_t hud_input{};

void InitOrb()
{
	me = *(Object**)offset.oLocalPlayer;
	heroes = *(ObjList**)offset.oHeroList;
	turrets = *(ObjList**)offset.oTurretList;
	//inhibitors = *(ObjList**)offsets.oInhibitorList;
	minions = *(ObjList**)offset.oMinionList;
	hud_input = *(uintptr_t*)(*(uintptr_t*)offset.oHudInstance + 0x48);
	p_aco = (bool*)(*(uintptr_t*)(*(uintptr_t*)offset.oHudInstance + 0x60) + 0x30);

}

Object* GetTarget(const Type type)
{
	Object* target = nullptr;
	if (type == Type::AutoKite)
	{
		target = heroes->GetLowestHealth(me, false);
	}
	if (type == Type::CleanLane)
	{
		target = minions->GetLowestHealth(me, true);
		if (target == nullptr)
		{
			target = turrets->GetLowestHealth(me, false);
		}
	}
	return target;
}

void Attack(Object* obj)
{
	const auto pos = WorldToScreen(obj->position);
	IssueOrder(hud_input, 0, 0, 1, pos.x, pos.y, 1);
}

void Move()
{
	if (POINT pos; GetCursorPos(&pos))
	{
		IssueOrder(hud_input, 0, 0, 0, pos.x, pos.y, 0);
	}
}

void Execute(Type type)
{
	static float last_attack_time{};
	static float last_move_time{};
	if (!me || IsChatOpen() || IsLeagueInBackground()) return;
	const auto now = GameTime();
	if (const auto target = GetTarget(type); target &&
		now > last_attack_time + me->ad() + 15e-3f)
	{
		last_attack_time = now;
		last_object = target;
		Attack(target);
	}
	else if (now > last_move_time + 33e-3f &&
		now > last_attack_time + me->acd() + 30e-3f)
	{
		last_move_time = now;
		Move();
	}
}
