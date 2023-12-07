//#pragma once
//
//#include "agent/script.hpp"
//#include "memory/function.hpp"
//
//class Cassiopeia : public script {
//  bool can_attack() override {
//    return Object::self()->state() & CanCast && Object::self()->GetSpell(SpellSlot_E)->level() > 0
//        && Object::self()->get_mana_cost(SpellSlot_E) <= Object::self()->mana() && !Object::self()->IsCasting();
//  };
//  bool is_reloading() override { return game_time < Object::self()->GetSpell(SpellSlot_E)->readyTime() - ping(); };
//  bool is_attacking() override { return false; };
//  void attack() override {
//    auto obj = get_skill_target(real_range());
//    if (obj && can_attack() && can_do_action()) {
//      PressKeyAt(SpellSlot_E, obj->position());
//    } else idle();
//  };
//  float real_range() override { return 700.f; };
//};