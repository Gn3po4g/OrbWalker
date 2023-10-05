#include "pch.hpp"

#include "struct.hpp"

#include "config/config.hpp"
#include "memory/global.hpp"

using namespace std;

vector<Object *> ObjList::objects_in_range(float range, bool collision) {
  vector<Object *> result;
  result.reserve(size);
  ranges::copy_if(std::span(data, size), back_inserter(result), [&](Object *obj) {
    return obj->IsValidTarget() && !(obj->IsPlant() || obj->IsWard())
        && obj->position() - self->position() <= range + (collision ? obj->BonusRadius() : 0.f);
  });
  return result;
}

Object *ObjList::best_object_in_range(float range, bool collision) {
  const auto &list = objects_in_range(range, collision);
  auto target = ranges::min_element(list, {}, [](Object *obj) {
    using config::Targeting;
    if(config::targeting == Targeting::health_lowest) {
      return obj->health();
    } else if(config::targeting == Targeting::distance_closest) {
      return obj->position() - self->position();
    } else {
      return obj->health();
    }
  });
  return target == list.end() ? nullptr : *target;
}