#pragma once

#include "object.hpp"

class ObjList : public RiotArray<Object *> {
public:
  static ObjList *heros();
  static ObjList *minions();
  static ObjList *turrets();
  static ObjList *inhibs();

  std::vector<Object *> all();
  Object *best_object(std::function<bool(Object *)>, Object *specific);
  static Object *
  get_object_in(std::initializer_list<ObjectType>, std::function<bool(Object *)>, Object *specific = nullptr);
};