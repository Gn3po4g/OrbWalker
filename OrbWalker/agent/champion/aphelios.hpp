#pragma once

#include "agent/script.hpp"

class Aphelios : public script {
  bool in_attack_range(Object *obj) override {
    if (has_buff(obj, "aphelioscalibrumbonusrangedebuff")) {
      return obj->position() - Object::self()->position()
          <= 1800.f + Object::self()->BonusRadius() + obj->BonusRadius();
    } else {
      return obj->position() - Object::self()->position()
          <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius();
    }
  }
};