#include "pch.hpp"

#include "obj_list.hpp"

#include "config/config.hpp"
#include "memory/offset.hpp"

using namespace std;

ObjList *ObjList::heros() { return Read<ObjList *>(RVA(oHeroList)); }

ObjList *ObjList::minions() { return Read<ObjList *>(RVA(oMinionList)); }

ObjList *ObjList::turrets() { return Read<ObjList *>(RVA(oTurretList)); }

ObjList *ObjList::inhibs() { return Read<ObjList *>(RVA(oInhibList)); }

std::vector<Object *> ObjList::all() { return span(data, size) | ranges::to<vector>(); }

Object *ObjList::best_object(std::function<bool(Object *)> fun, Object *specific) {
  const auto &list = span(data, size) | views::filter([fun](Object *obj) { return obj->IsValidTarget() && fun(obj); })
                   | ranges::to<vector>();
  if (ranges::contains(list, specific)) return specific;
  const auto target = ranges::min_element(list, {}, [](Object *obj) {
    const auto &config = config::inst();
    if (config.selector == HealthHighest) {
      return -obj->health();
    } else if (config.selector == HealthPercentLowest) {
      return obj->health() / obj->max_health();
    } else if (config.selector == DistanceClosest) {
      return distance(obj->position(), Object::self()->position());
    } else {
      return obj->health();
    }
  });
  return target == list.end() ? nullptr : *target;
}

Object *ObjList::get_object_in(initializer_list<ObjectType> types, function<bool(Object *)> fun, Object *specific) {
  Object *ret{};
  if (ranges::contains(types, Hero)) { ret = heros()->best_object(fun, specific); }
  if (!ret && ranges::contains(types, Minion)) { ret = minions()->best_object(fun, nullptr); }
  if (!ret && ranges::contains(types, Turret)) { ret = turrets()->best_object(fun, nullptr); }
  if (!ret && ranges::contains(types, Inhibitor)) { ret = inhibs()->best_object(fun, nullptr); }
  return ret;
}
