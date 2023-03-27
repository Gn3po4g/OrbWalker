#include "pch.h"

using namespace std;

Object *ObjList::GetLowestHealth(Object *me) const {
    static Object *previous = nullptr;
    span<Object *> obj_list(list, size);
    Object* current = nullptr;
    float min_health = FLT_MAX;
    for (auto obj : obj_list) {
      if (Functions::IsAlive(obj) && obj->team != me->team && obj->visible && obj->targetable
        && obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR() && obj != previous) {
        if (obj->health < min_health) {
          min_health = obj->health;
          current = obj;
        }
      }
    }
    previous = current;
    return current;
}

Object *ObjList::GetLastHit(Object *me) const {
  static Object* previous = nullptr;
  span<Object*> obj_list(list, size);
  for (auto obj : obj_list) {
    if (Functions::IsAlive(obj) && obj->team != me->team && obj->visible && obj->targetable
      && obj->DistanceTo(me) <= me->attack_range + obj->GetBR() + me->GetBR() && obj != previous) {
      if (obj->health < me->base_attack + me->bonus_attack) {
        previous = obj;
        return obj;
      }
    }
  }
  return nullptr;
}