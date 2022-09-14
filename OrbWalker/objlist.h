#pragma once
#include "object.h"

class ObjList {
public:
	char pad_0x0000[0x4];
	Object** list; //0x0004
	int size; //0x0008
};
