#pragma once

#include "object.hpp"

class ObjList : public RiotArray<Object *> {
public:
  Object *best_object(std::function<bool(Object *)>);
  bool contains(Object*);
};