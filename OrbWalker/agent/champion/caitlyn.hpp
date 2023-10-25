#pragma once

#include "agent/script.hpp"
#include "memory/offset.hpp"

class Caitlyn : public script {
  bool in_attack_range(Object *obj) override {
    if(has_buff(obj, "CaitlynEMissile") || has_buff(obj, "CaitlynWSnare")) {
      return obj->position() - self->position() <= 1300.f + self->BonusRadius() + obj->BonusRadius();
    } else {
      return obj->position() - self->position() <= self->attack_range() + self->BonusRadius() + obj->BonusRadius();
    }
  }
};