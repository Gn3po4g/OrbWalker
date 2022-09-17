#pragma once
#include "object.h"
#include "objlist.h"

class OrbWalker {
public:
	OrbWalker();
	void AttackObject(bool);
	std::unique_ptr<Object> me;
	std::unique_ptr<ObjList> heroes;
	std::unique_ptr<ObjList> turrets;
	std::unique_ptr<ObjList> inhibitors;
	std::unique_ptr<ObjList> minions;
private:
	long lastAttackTime = 0;
	long lastMoveTime = 0;
	[[nodiscard]] Object* FindTarget(bool) const;
	[[nodiscard]] Object* GetObjFromList(const ObjList*) const;
};

extern std::unique_ptr<OrbWalker> orbWalker;
