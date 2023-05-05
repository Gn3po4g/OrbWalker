#include "pch.h"

using namespace std;

auto GetObjectList(const ObjList* const list) {
  return span(*(Object***)((uintptr_t)list + 0x8), *(int*)((uintptr_t)list + 0x10));
}

Object* ObjList::get_lowest_health(Object* const me) const {
  Object* current = nullptr;
  float min_health = FLT_MAX;
  for (const auto obj : GetObjectList(this)) {
    if (obj->AttackableFor(me) && obj->InRangeOf(me)) {
      if (obj->health() < min_health) {
        min_health = obj->health();
        current = obj;
      }
    }
  }
  return current;
}

Object* ObjList::get_last_hit(Object* const me) const {
  for (const auto obj : GetObjectList(this)) {
    if (obj->AttackableFor(me) && obj->InRangeOf(me)) {
      if (obj->health() < me->attack()) {
        return obj;
      }
    }
  }
  return nullptr;
}
