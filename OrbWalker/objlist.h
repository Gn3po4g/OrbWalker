#pragma once

extern Object* last_object;

class ObjList {
public:
  Object* GetLowestHealth(Object* const, const bool) const;
  Object* GetLastHit(Object* const) const;
};