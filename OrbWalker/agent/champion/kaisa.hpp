#pragma once

#include "agent/script.hpp"

class Kaisa : public Script {
  void run(SpellCast *spell_cast, Object *obj) override {
    std::string name = *(RiotString16 *)(*(uintptr_t *)spell_cast + 0x28);
    if(spell_cast->type() == -1 || name == "KaisaPAttack" || name == "KaisaEPAttack") last_attack_time = game_time;
  }
  bool can_attack() override { return Script::can_attack() && !has_buff("KaisaE"); };
};