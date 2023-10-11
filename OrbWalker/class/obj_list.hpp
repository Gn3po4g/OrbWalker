#pragma once

#include "object.hpp"

class ObjList : public RiotArray<Object *> {
public:
  std::vector<Object *> objects_in_range(float, bool);
  Object *best_object_in_range(float, bool);
};