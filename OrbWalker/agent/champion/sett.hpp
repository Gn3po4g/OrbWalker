#pragma once

#include "agent/script.hpp"

constexpr auto first_attack = std::to_array<std::string_view>({"SettBasicAttack", "SettBasicAttack3", "SettQAttack"});

class Sett : public script {
  void run(SpellCast *spell_cast, Object *obj) override {
    if(spell_cast->is_attack()) last_attack_time = game_time;
    if(spell_cast->name() == "SettQ") last_attack_time = -FLT_MAX;
    last_spell_name = spell_cast->name();
  }
  bool is_reloading() override {
    if(std::ranges::count(first_attack, last_spell_name)) {
      return game_time < last_attack_time + (self->AttackDelay() - 0.1f) / 2.5;
    }
    return game_time < last_attack_time + self->AttackDelay() - 0.1f;
  }

private:
  std::string last_spell_name{};
};