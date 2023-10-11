#pragma once

 #include "agent/script.hpp"
 #include "memory/function.hpp"
 #include "memory/global.hpp"

class Cassiopeia : public Script {
  bool can_attack() override {
    return self->state() & CanCast && self->GetSpell(2)->level() > 0
        && self->get_mana_cost(2) <= self->mana();
  };
  bool is_reloading() override { return game_time < self->GetSpell(2)->readyTime() - interval; };
  bool is_attacking() override { return false; };
  void attack() override {
    auto obj = get_target(real_range(), false);
    if(obj && !obj->IsBuilding() && can_attack() && can_do_action()) {
      CastSpell(obj, 2);
    } else idle();
  };
  float real_range() override { return 700.f; };
};