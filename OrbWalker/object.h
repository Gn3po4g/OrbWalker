#pragma once
#include "vector.h"

class Object {
public:
	char pad_0x0000[0x34];
	int team; //0x0034
	char pad_0x0038[0x1A4];
	Vector3 position; //0x01DC
	char pad_0x01E8[0x8C];
	bool visible; //0x0274
	char pad_0x0275[0xA8F];
	bool targetable; //0x0D04
	char pad_0x0D05[0x697];
	float attackRange; //0x139C

	float DisTo(const Object*) const;
	bool IsAlive();
	int GetAttackDelayTicks();
	int GetAttackCastDelayTicks();
};