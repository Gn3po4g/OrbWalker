#pragma once

#include "renderer.h"


class OrbWalker {
	Renderer* renderer;
	Object* me;
	ObjList* heroes;
	ObjList* turrets;
	ObjList* inhibitors;
	ObjList* minions;
	float lastAttackTime = 0;
	float lastMoveTime = 0;

	Object* FindTarget(const bool&);
public:
	OrbWalker();
	void AttackObject(const bool&);
};