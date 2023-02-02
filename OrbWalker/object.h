#pragma once

#include "defines.h"
#include "object.h"
#include "vector.h"

class Object {
public:
	union {
		DEFINE_MEMBER_N(short, team, 0x34);
		DEFINE_MEMBER_N(Vector3, position, 0x1DC);
		DEFINE_MEMBER_N(bool, visible, 0x274); 
		DEFINE_MEMBER_N(bool, targetable, 0xD04);
		DEFINE_MEMBER_N(float, attackRange, 0x13A4);
	};

	float DistanceTo(const Object* other) const
	{
		return position.DistanceTo(other->position);
	}
};