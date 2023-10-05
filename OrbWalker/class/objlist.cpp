#include "pch.hpp"

#include "struct.hpp"

#include "agent/orb.hpp"
#include "config/config.hpp"
#include "memory/global.hpp"

std::vector<Object *> ObjList::objects_in_range(float range, bool collision) {
  return std::span(data, size) | std::views::filter([&](Object *obj) {
           return obj->IsValidTarget()
               && obj->position() - self->position() <= range + (collision ? obj->BonusRadius() : 0.f);
         })
       | std::ranges::to<std::vector>();
}

Object *ObjList::best_object_in_range(float range, bool collision) {
  const auto &list = objects_in_range(range, collision);
  auto target = std::ranges::min_element(list, {}, [](Object *obj) {
    using config::Targeting;
    if(config::targeting == Targeting::health_lowest) {
      return obj->health();
    } else if(config::targeting == Targeting::distance_closest) {
      return obj->position() - self->position();
    } else {
      return obj->health();
    }
  });
  if(target == list.end()) return nullptr;
  else return *target;
}