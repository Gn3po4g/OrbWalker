#pragma once

#include "object.hpp"

enum selector : int { health_lowest, health_highest, health_percent_lowest, distance_closest, count };

const std::map<int, std::string> selector_map{
  {health_lowest,         "health_lowest"        },
  {health_highest,        "health_highest"       },
  {health_percent_lowest, "health_percent_lowest"},
  {distance_closest,      "distance_closest"     }
};

class ObjList : public RiotArray<Object *> {
public:
  static ObjList *heros();
  static ObjList *minions();
  static ObjList *turrets();
  static ObjList *inhibs();

  Object *best_object(std::function<bool(Object *)>, Object *specific);
  static Object *get_in_order(int, std::function<bool(Object *)>, Object *specific = nullptr);
};