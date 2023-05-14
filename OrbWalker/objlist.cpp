#include "pch.h"

Object* last_object = nullptr;

using namespace std;

auto GetObjectList(const ObjList* const list) {
  return span(*(Object***)((uintptr_t)list + 0x8), *(int*)((uintptr_t)list + 0x10));
}

Object* ObjList::GetLowestHealth(Object* const me, const bool diff) const {
  auto filtered = GetObjectList(this) | views::filter([&](Object* obj) {return obj->AttackableFor(me) && obj->InRangeOf(me); }) | ranges::to<vector>();
  if (filtered.empty()) return nullptr;
  if (filtered.size() == 1) return filtered[0];
  if (diff) {
    return *ranges::min_element(filtered, [](Object* o, Object* smallest) {
      if (o == last_object) return false;
      else if (smallest == last_object) return true;
      else return o->health() < smallest->health();
      });
  }
  else {
    return *ranges::min_element(filtered);
  }
}