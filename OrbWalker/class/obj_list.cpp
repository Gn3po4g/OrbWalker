#include "pch.hpp"

#include "obj_list.hpp"

#include "config/config.hpp"
#include "memory/offset.hpp"

using namespace std;

ObjList *ObjList::heros() { return Read<ObjList *>(RVA(oHeroList)); }

ObjList *ObjList::minions() { return Read<ObjList *>(RVA(oMinionList)); }

ObjList *ObjList::turrets() { return Read<ObjList *>(RVA(oTurretList)); }

ObjList *ObjList::inhibs() { return Read<ObjList *>(RVA(oInhibList)); }

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
      return obj->position() - Object::self()->position();
    } else if (config.selector == health_percent_lowest) {
      return obj->health() / obj->max_health();
    }
    return obj->health();
  });
  return target == list.end() ? nullptr : *target;
}

Object *ObjList::get_in_order(int type, std::function<bool(Object *)> fun, Object *specific) {
  if (type == Hero) {
    return heros()->best_object(fun, specific);
  } else {
    Object *ret{};
    if (!ret && (type & Minion)) { ret = minions()->best_object(fun, nullptr); }
    if (!ret && (type & Building)) { ret = turrets()->best_object(fun, nullptr); }
    if (!ret && (type & Building)) { ret = inhibs()->best_object(fun, nullptr); }
    return ret;
  }
}
