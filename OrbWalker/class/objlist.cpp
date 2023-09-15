#include "stdafx.hpp"

std::set<ObjectType> hashes{ObjectType::Hero, ObjectType::Minion_Lane, ObjectType::Monster, ObjectType::Turret};

std::span<Object *> ObjList::data() {
  return std::span(prop<Object **>(0x8), prop<int>(0x10));
}

Object *ObjList::GetAppropriateObject() {
  auto objList = data() | std::views::filter([](Object *obj) {
                   return obj->IsValidTarget() && hashes.contains(obj->type());
                 });
  auto target = std::ranges::min_element(objList, {}, [self = script::self](Object *obj) {
    using config::Targeting;
    if(config::targeting == (int)Targeting::health_lowest) {
      return obj->health();
    } else if(config::targeting == (int)Targeting::distance_closest) {
      return obj->position() - self->position();
    } else {
      return obj->health();
    }
  });
  if(target == objList.end()) {
    return nullptr;
  } else {
    return *target;
  }
}

bool ObjList::Contains(Object *obj) {
  return std::ranges::find(data(), obj) != data().end();
}