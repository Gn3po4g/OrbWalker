#pragma once

class ObjList {
public:
	PAD(0x4);
	Object** list;
	int size;

	Object* GetLowestHealth(const Object*);
	Object* GetLastHit(const Object*);
};