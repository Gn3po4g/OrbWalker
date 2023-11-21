#pragma once

#include "agent/script.hpp"

class Aphelios : public script {
  bool in_attack_range(Object *obj) override {
    return distance(obj->position(), Object::self()->position())
        <= (obj->has_buff("ApheliosCalibrumBonusRangeDebuff"_FNV) ? 1800.f : Object ::self()->attack_range())
             + Object::self()->BonusRadius() + obj->BonusRadius();
  }
};