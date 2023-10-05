#include "pch.hpp"

#include "orb.hpp"
#include "script.hpp"

#include "memory/function.hpp"
#include "memory/global.hpp"

Object *GetTarget(float range, bool collision) {
  if(orb->orbState == Orb::OrbState::Kite) {
    if(std::ranges::count(heros->objects_in_range(range, collision), orb->markedObject)) {
      return orb->markedObject;
    } else {
      return heros->best_object_in_range(range, collision);
    }
  } else if(orb->orbState == Orb::OrbState::Clear) {
    if(const auto target = minions->best_object_in_range(range, collision);
       target->IsLaneMinion() || target->IsJungle()) {
      return target;
    } else {
      return turrets->best_object_in_range(range, collision);
    }
  } else {
    return nullptr;
  }
}

void Script::update() {
  game_time = function::GameTime();
  extra_update();
}

void Script::extra_update() {
  auto spell_cast = self->spell_cast();
  if(spell_cast && (*(int *)(spell_cast + 0x10) == -1 || *(int *)(spell_cast + 0x124) >= 14) && spell_cast != last_spell_cast) {
    last_attack_time = game_time;
  }
  last_spell_cast = spell_cast;
}

bool Script::can_attack() { return self->state() & CharacterState::CanAttack; }

bool Script::can_do_action() {
  if(game_time < last_action_time + interval) return false;
  last_action_time = game_time;
  return true;
}

bool Script::is_reloading() { return game_time < last_attack_time + self->AttackDelay() - .09f; }

bool Script::is_attacking() { return game_time < last_attack_time + self->AttackWindup() - .03f; }

void Script::idle() {
  if(!is_attacking() && can_do_action()) function::Move2Mouse();
}

void Script::attack() {
  auto obj = GetTarget(draw_range(), true);
  if(obj && can_attack() && can_do_action()) {
    function::AttackObject(obj);
  } else {
    idle();
  }
}

float Script::draw_range() { return self->RealAttackRange(); }

bool Script::has_buff(std::string_view name) {
  return std::ranges::any_of(self->buffs(), [name, this](Buff *buff) {
    return buff->name() == name && buff->starttime() <= game_time && buff->endtime() >= game_time;
  });
}

void Ashe::extra_update() {
  auto spell_cast = self->spell_cast();
  if(spell_cast && *(int *)(spell_cast + 0x124) == 0 && spell_cast != last_spell_cast) { last_attack_time = -FLT_MAX; }
  Script::extra_update();
}

void Cassiopeia::extra_update() {
  // if(orb->orbState == Orb::OrbState::Off) return;
  // auto obj = GetTarget(850.f, false);
  // if(obj && obj->type() != ObjectType::Turret && orb->self->state() & CharacterState::CanCast
  //&& orb->self->GetSpell(0)->level() > 0 && orb->self->mana_cost(0) <= orb->self->mana()
  //&& game_time >= orb->self->GetSpell(0)->readyTime() && can_do_action()) {
  //   function::CastSpell(obj->position(), 0);
  // }
}

bool Cassiopeia::can_attack() {
  return self->state() & CharacterState::CanCast && self->GetSpell(2)->level() > 0
      && self->get_mana_cost(2) <= self->mana();
}

bool Cassiopeia::is_reloading() { return game_time < self->GetSpell(2)->readyTime() - interval; }

void Cassiopeia::attack() {
  auto obj = GetTarget(draw_range(), false);
  if(obj && !obj->IsTurret() && can_attack() && can_do_action()) {
    function::CastSpell(obj, 2);
  } else idle();
}

float Cassiopeia::draw_range() { return 700.f; }

bool Graves::is_reloading() { return game_time < last_attack_time + self->AttackDelay() * .15f - .09f; }

bool Kaisa::can_attack() { return Script::can_attack() && !has_buff("KaisaE"); }

bool Zeri::can_attack() { return self->state() & CharacterState::CanCast; }

bool Zeri::is_reloading() { return game_time < self->GetSpell(0)->readyTime() - interval; }

void Zeri::attack() {
  auto obj = GetTarget(draw_range(), false);
  if(obj && can_attack() && can_do_action()) function::CastSpell(obj->position(), 0);
  else idle();
}

float Zeri::draw_range() { return self->RealAttackRange() - self->BonusRadius() + 250.f; }
