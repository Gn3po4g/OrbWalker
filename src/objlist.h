#pragma once

class ObjList {
public:
	PAD(0x4);
	Object** list;
	int size;
};

class HeroList : public ObjList {
public:
	Object* GetLowestHealth(const Object*) const;
};

class MinionList : public ObjList {
public:
	Object* GetLowestHealth(const Object*) const;
	Object* GetLastHit(const Object*) const;
};