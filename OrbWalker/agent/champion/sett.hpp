#pragma once

#include "agent/script.hpp"

constexpr auto first_attack = std::to_array<std::string_view>({"SettBasicAttack", "SettBasicAttack3", "SettQAttack"});

class Sett : public script {
  bool is_reloading() override {
    if (std::ranges::count(first_attack, last_cast_spell->name())) {
      return game_time < last_attack_time + self->AttackDelay() / 2.5;
    }
    return game_time < last_attack_time + self->AttackDelay();
  }
};