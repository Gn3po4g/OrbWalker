#pragma once
#include "object.h"
#include "objlist.h"
#include "renderer.h"

class OrbWalker {
public:
	OrbWalker();
	void AttackObject(bool);
	Renderer* renderer;
	Object* me;
	ObjList* heroes;
	std::unique_ptr<ObjList> turrets;
	std::unique_ptr<ObjList> inhibitors;
	std::unique_ptr<ObjList> minions;
private:
	float lastAttackTime = 0;
	float lastMoveTime = 0;
	Object* FindTarget(bool) const;
	Object* GetObjFromList(const ObjList*) const;
};

extern std::unique_ptr<OrbWalker> orbWalker;
