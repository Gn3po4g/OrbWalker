#pragma once

#include "agent/script.hpp"

class Akshan : public script {
  bool is_reloading() override {
    if (last_cast_spell == "AkshanBasicAttack") {
      return false;
    }
    return game_time < last_attack_time + Object::self()->AttackDelay();
  }
};