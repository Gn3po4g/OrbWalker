#pragma once

#include "agent/script.hpp"

class Aphelios : public Script {
  void run(SpellCast *spell_cast, Object *obj) override {
    // static std::vector<std::string> attack_spells{
    //   "ApheliosCalibrumAttack", "ApheliosCalibrumAttackOverride", "ApheliosGravitumAttack", "ApheliosInfernumAttack",
    //   "ApheliosSeverumAttack"};
    // std::string name = *(RiotString16 *)(*(uintptr_t *)spell_cast + 0x28);
    // if(spell_cast->type() == -1 || std::ranges::count(attack_spells, name)) last_attack_time = game_time;
    Script::run(spell_cast, obj);
    // if(spell_cast->slot() == SpellSlot_Q) last_attack_time = -FLT_MAX;
    if(spell_cast->name() == "ApheliosCrescendumAttack") last_attack_time = -FLT_MAX;
  };
};