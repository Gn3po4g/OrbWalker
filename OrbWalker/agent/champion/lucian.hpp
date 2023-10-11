#pragma once

#include "agent/script.hpp"

class Lucian : public Script {
  void run(SpellCast *spell_cast, Object *obj) override {
    Script::run(spell_cast, obj);
    if(spell_cast->slot() == SpellSlot_E) last_attack_time = -FLT_MAX;
  }
};