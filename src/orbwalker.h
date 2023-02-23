#pragma once

#include "renderer.h"

class OrbWalker {
	static Renderer* renderer;
	static Object* me;
	static ObjList* heroes;
	static ObjList* turrets;
	static ObjList* inhibitors;
	static ObjList* minions;
	static DWORD_PTR HUDInput;
	static XMFLOAT3* MousePos;
	static ULONGLONG lastAttackTime;
	static ULONGLONG lastMoveTime;
public:
	static void Initialize();
	static void AttackChampion();
	static void CleanLane();
	static void LastHit();
};