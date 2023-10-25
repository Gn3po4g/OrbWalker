#include "pch.hpp"

#include "obj_list.hpp"

#include "config/config.hpp"
#include "memory/offset.hpp"

using namespace std;

Object *ObjList::best_object(std::function<bool(Object *)> fun, Object *specific) {
  const auto &list =
    span(data, size)
    | views::filter([fun](Object *obj) { return obj->IsValidTarget() && obj->max_health() > 6.f && fun(obj); })
    | ranges::to<vector>();
  if (ranges::count(list, specific)) return specific;
  const auto target = ranges::min_element(list, {}, [](Object *obj) {
    const auto &config = config::inst();
    if (config.selector == health_highest) {
      return -obj->health();
    } else if (config.selector == distance_closest) {
      return obj->position() - self->position();
    } else if (config.selector == health_percent_lowest) {
      return obj->health() / obj->max_health();
    }
    return obj->health();
  });
  return target == list.end() ? nullptr : *target;
}

bool ObjList::contains(Object *obj) { return ranges::count(span(data, size), obj); }
