#pragma once

#include "renderer.h"

enum Type { space, v, x };

class OrbWalker {
	static Renderer* renderer;
	static Object* me;
	static HeroList* heroes;
	static ObjList* turrets;
	static ObjList* inhibitors;
	static MinionList* minions;
	static DWORD_PTR HUDInput;
	static XMFLOAT3* MousePos;
	static ULONGLONG lastAttackTime;

	static Object* FindTarget(const Type&);
public:
	static void Initialize();
	static void AttackObject(const Type&);
};