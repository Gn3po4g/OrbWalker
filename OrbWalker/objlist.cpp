#include "pch.h"

using namespace std;

Object* ObjList::get_lowest_health(Object* me) const{
    Object* current = nullptr;
    float min_health = FLT_MAX;
    for (const span obj_list(
             *reinterpret_cast<Object***>(reinterpret_cast<uintptr_t>(this) + 0x8),
             *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x10));
         const auto obj : obj_list)
    {
        if (Functions::IsAlive(obj) && obj->team() != me->team() &&
            obj->visible() && obj->targetable() &&
            obj->DistanceTo(me) <= me->attack_range() + obj->br() + me->br())
        {
            if (obj->health() < min_health)
            {
                min_health = obj->health();
                current = obj;
            }
        }
    }
    return current;
}

Object* ObjList::get_last_hit(Object* me) const{
    for (const span obj_list(
             *reinterpret_cast<Object***>(reinterpret_cast<uintptr_t>(this) + 0x8),
             *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x10));
         const auto obj : obj_list)
    {
        if (Functions::IsAlive(obj) && obj->team() != me->team() &&
            obj->visible() && obj->targetable() &&
            obj->DistanceTo(me) <= me->attack_range() + obj->br() + me->br())
        {
            if (obj->health() < me->base_attack() + me->bonus_attack())
            {
                return obj;
            }
        }
    }
    return nullptr;
}
