#include "pch.h"

Object* last_object = nullptr;

using namespace std;

auto GetObjectList(const ObjList* const list) {
  return span(*(Object***)((uintptr_t)list + 0x8), *(int*)((uintptr_t)list + 0x10));
}

Object* ObjList::GetLowestHealth(Object* const me, const bool diff) const {
  auto filtered = GetObjectList(this) | views::filter([&](Object* obj) {return obj->AttackableFor(me) && obj->InRangeOf(me); }) | ranges::to<vector>();
  if (filtered.size() == 1) return filtered[0];
  ranges::sort(filtered, [](Object* o1, Object* o2) {return o1->health() < o2->health(); });
  if (diff) {
    auto ret = ranges::find_if(filtered, [](Object* obj) {return obj != last_object; });
    return ret != filtered.end() ? *ret : nullptr;
  }
  else {
    return filtered.empty() ? nullptr : filtered[0];
  }
}

Object* ObjList::GetLastHit(Object* const me) const {
  auto filtered = GetObjectList(this) | views::filter([&](Object* obj) {return obj->AttackableFor(me) && obj->InRangeOf(me); }) | ranges::to<vector>();
  if (filtered.size() == 1) return filtered[0];
  auto ret = ranges::find_if(filtered, [&](Object* obj) {return obj != last_object && obj->health() <= me->attack(); });
  return ret != filtered.end() ? *ret : nullptr;
}
