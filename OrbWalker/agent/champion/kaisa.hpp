#pragma once

#include "agent/script.hpp"

class Kaisa : public Script {
  //void run(int arg, SpellCast *spell_cast, Object *obj) override {
  //  if(spell_cast->type() == -1 || spell_cast->id() == 0x3F) last_attack_time = game_time;
  //}
  bool can_attack() override { return Script::can_attack() && !has_buff("KaisaE"); };
};