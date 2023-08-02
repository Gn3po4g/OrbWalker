#include "object.hpp"
#include "function.hpp"
#include <span>
#include <ranges>

float Object::ad()
{
  return AttackDelay(this);
}

float Object::acd()
{
  return AttackCastDelay(this);
}


bool Object::AttackableFor(Object* other)
{
  return team != other->team && visible && targetable && IsAlive(this);
}

bool Object::InRangeOf(Object* other)
{
  const float dx = position.x - other->position.x;
  const float dy = position.y - other->position.y;
  const float dz = position.z - other->position.z;
  return sqrtf(dx * dx + dy * dy + dz * dz) <=
    other->attackrange + BonusRadius(this) + BonusRadius(other);
}

Object* last_object = nullptr;

using namespace std;

auto dif_cmp = [](Object* o, Object* smallest)
{
  return o->health < smallest->health && o != last_object || smallest == last_object;
};

Object* ObjList::GetLowestHealth(Object* me, bool diff)
{
  auto filtered = span(list, size) |
    views::filter([me](Object* obj)
    {
      return obj->AttackableFor(me) && obj->InRangeOf(me);
    });
  auto num = ranges::distance(filtered);
  if (num == 0) return nullptr;
  if (num == 1) return filtered.front();
  return diff ? *ranges::min_element(filtered, dif_cmp) : *ranges::min_element(filtered);
}
