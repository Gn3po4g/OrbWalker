#pragma once

#include <DirectXMath.h>
#include <cstddef>

#define OFFSET(type,offset) (*(type*)((uintptr_t)this+offset))

class Object {
	int team();
	bool visible();
	bool targetable();
	float attackrange();
public:
	DirectX::XMFLOAT3 position();
	float health();
	float AttackDelay();
	float AttackWindup();
	bool IsAlive();
	bool AttackableFor(Object*);
	bool InRangeOf(Object*);
};

extern Object* last_object;

class ObjList {
	Object** list();
	int size();
public:
	Object* GetLowestHealth(Object*, bool);
};
