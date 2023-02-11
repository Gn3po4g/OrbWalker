#pragma once

#include "renderer.h"


class OrbWalker {
	const Renderer* renderer;
	const Object* me;
	const ObjList* heroes;
	const ObjList* turrets;
	const ObjList* inhibitors;
	const ObjList* minions;
	const DWORD HUDInput;
	const XMFLOAT3* MousePos;
	ULONGLONG lastAttackTime{};

	Object* FindTarget(const bool&) const;
public:
	OrbWalker();
	void AttackObject(const bool&);
};