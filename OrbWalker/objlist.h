#pragma once

#include "object.h"
#include "defines.h"

class ObjList {
public:
	union {
		DEFINE_MEMBER_N(Object**, list, 0x4);
		DEFINE_MEMBER_N(int, size, 0x8);
	};
};
