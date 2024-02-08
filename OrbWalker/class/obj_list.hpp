#pragma once

#include "object.hpp"

enum type : u8 { hero = 0, minion = 1 << 0, turret = 1 << 1, inhibitor = 1 << 2 };

class ObjList : public RiotArray<Object *> {
public:
  static ObjList *heros();
  static ObjList *minions();
  static ObjList *turrets();
  static ObjList *inhibs();

  std::vector<Object *> all();
  Object *best_object(std::function<bool(Object *)>, Object *specific);
  static Object *get_object_in(u8, std::function<bool(Object *)>, Object *specific = nullptr);
};