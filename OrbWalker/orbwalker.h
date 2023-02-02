#pragma once

#include "object.h"
#include "objlist.h"
#include "renderer.h"
#include "utils.h"

inline Renderer* renderer;
inline Object* me;
inline ObjList* heroes;
inline ObjList* turrets;
inline ObjList* inhibitors;
inline ObjList* minions;

inline float lastAttackTime = 0;
inline float lastMoveTime = 0;

inline void InitOrbWalker()
{
	renderer = static_cast<Renderer*>(oViewProjMatrices);
	me = *static_cast<Object**>(oLocalPlayer);
	heroes = *static_cast<ObjList**>(oHeroList);
	turrets = *static_cast<ObjList**>(oTurretList);
	inhibitors = *static_cast<ObjList**>(oInhibitorList);
	minions = *static_cast<ObjList**>(oMinionList);
}

inline Object* GetObjFromList(const ObjList* list)
{
	Object* ret = nullptr;
	for (int i = 0; i < list->size; i++)
	{
		if (IsAlive(list->list[i])
			&& list->list[i]->team != me->team
			&& list->list[i]->visible
			&& list->list[i]->targetable
			&& list->list[i]->DistanceTo(me) <= me->attackRange)
		{
			if (!ret) ret = list->list[i];
			else if (list->list[i]->DistanceTo(me) < ret->DistanceTo(me))ret = list->list[i];
		}
	}
	return ret;
}

inline Object* FindTarget(const bool findHero)
{
	if (findHero) return GetObjFromList(heroes);
	Object* target = GetObjFromList(turrets);
	if (!target) target = GetObjFromList(inhibitors);
	if (!target) target = GetObjFromList(minions);
	return target;
}


inline void AttackObject(bool findHero)
{
	if (const Object* target = FindTarget(findHero); target
		&& GetGameTime() >= lastAttackTime + GetAttackDelay(me))
	{
		Attack(renderer->WorldToScreen(target->position));
		lastAttackTime = GetGameTime();
	}
	else if (GetGameTime() > lastMoveTime + .03f
		&& GetGameTime() >= lastAttackTime + GetAttackCastDelay(me) + .09f)
	{
		Click(renderer->WorldToScreen(GetMouseWorldPosition()));
		lastMoveTime = GetGameTime();
	}
}