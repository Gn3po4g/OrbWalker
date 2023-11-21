#pragma once

#include "agent/script.hpp"

class Caitlyn : public script {
  bool in_attack_range(Object *obj) override {
    if (obj->has_buff("CaitlynEMissile"_FNV) || obj->has_buff("CaitlynWSnare"_FNV)) {
      return distance(obj->position(), Object::self()->position())
          <= 1300.f + Object::self()->BonusRadius() + obj->BonusRadius();
    } else {
      return distance(obj->position(), Object::self()->position())
          <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius();
    }
  }
};