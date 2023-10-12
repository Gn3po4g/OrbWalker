#pragma once

 #include "agent/script.hpp"
#include "memory/function.hpp"
 #include "memory/global.hpp"

class Zeri : public script {
public:
  bool can_attack() override { return self->state() & CanCast; };
  bool is_reloading() override { return game_time < self->GetSpell(0)->readyTime() - interval; };
  bool is_attacking() override { return false; };
  void attack() override {
    auto obj = get_target(real_range(), false);
    if(obj && can_attack() && can_do_action()) CastSpell(obj->position(), 0);
    else idle();
  };
  float real_range() override { return self->attack_range() + 250.f; };
};