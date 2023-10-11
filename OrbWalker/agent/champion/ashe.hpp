#pragma once

#include "agent/script.hpp"

class Ashe : public Script {
  void run(SpellCast *spell_cast, Object *obj) override {
    std::string name = *(RiotString16 *)(*(uintptr_t *)spell_cast + 0x28);
    if(spell_cast->type() == -1 || name == "AsheQAttack") last_attack_time = game_time;
    if(name == "AsheQ") last_attack_time = -FLT_MAX;
  }
};
