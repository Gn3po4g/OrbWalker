#pragma once

#include "agent/script.hpp"
#include "memory/offset.hpp"

class Aphelios : public script {
  bool in_attack_range(Object *obj) override {
    if(has_buff(obj, "aphelioscalibrumbonusrangedebuff")) {
      return obj->position() - self->position() <= 1800.f + self->BonusRadius() + obj->BonusRadius();
    } else {
      return obj->position() - self->position() <= self->attack_range() + self->BonusRadius() + obj->BonusRadius();
    }
  }
};