#pragma once

#include "object.hpp"

class ObjList : public RiotArray<Object *> {
public:
  Object *best_object(std::function<bool(Object *)>, Object *specific);
  bool contains(Object *);
};

template <std::unique_ptr<ObjList> &...args>
Object *get_in_order(std::function<bool(Object *)> fun, Object *specific = nullptr) {
  Object *ret{nullptr};
  ((ret = ret ? ret : args->best_object(fun, specific)), ...);
  return ret;
}