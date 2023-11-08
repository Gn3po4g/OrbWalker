#pragma once

#include "agent/script.hpp"
#include "memory/function.hpp"

class Zeri : public script {
public:
  bool can_attack() override { return Object::self()->state() & CanCast; };
  bool is_reloading() override {
    return game_time < Object::self()->GetSpell(SpellSlot_Q)->readyTime() - interval * 2;
  };
  bool is_attacking() override { return false; };
  void attack() override {
    auto obj = get_attack_target();
    if (obj && can_attack() && can_do_action()) PressKeyAt('Q', obj->position());
    else idle();
  };
  float real_range() override { return Object::self()->attack_range() + 250.f; };
  bool in_attack_range(Object *obj) override { return obj->position() - Object::self()->position() <= real_range(); }
};