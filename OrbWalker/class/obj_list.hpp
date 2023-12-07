#pragma once

#include "object.hpp"

#define ENUM(name, ...)                                                                                                \
  enum name : int { __VA_ARGS__ };                                                                                     \
  static inline std::vector name##_str = #__VA_ARGS__ | std::views::split(", "sv)                                             \
                                | std::views::transform([](auto v) { return std::string(v.begin(), v.end()); })        \
                                | std::ranges::to<std::vector>()

ENUM(selector, health_lowest, health_highest, health_percent_lowest, distance_closest);

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