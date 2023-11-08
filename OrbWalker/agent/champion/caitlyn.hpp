#pragma once

#include "agent/script.hpp"

class Caitlyn : public script {
  bool in_attack_range(Object *obj) override {
    if (has_buff(obj, "CaitlynEMissile") || has_buff(obj, "CaitlynWSnare")) {
      return obj->position() - Object::self()->position()
          <= 1300.f + Object::self()->BonusRadius() + obj->BonusRadius();
    } else {
      return obj->position() - Object::self()->position()
          <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius();
    }
  }
};