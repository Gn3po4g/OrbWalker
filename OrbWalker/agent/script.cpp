#include "pch.hpp"

#include "agent/champion/all.hpp"
#include "script.hpp"

#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"

script &script::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] {
    switch(FNV(self->name().data())) {
    case FNVC("Cassiopeia"):
      instance_.reset(new Cassiopeia);
      break;
    case FNVC("Graves"):
      instance_.reset(new Graves);
      break;
    case FNVC("Kaisa"):
      instance_.reset(new Kaisa);
      break;
    case FNVC("Zeri"):
      instance_.reset(new Zeri);
      break;
    default:
      instance_.reset(new script);
      break;
    }
  });
  return *instance_;
}

void script::run(SpellCast *spell_cast, Object *obj) {
  if(spell_cast->is_attack()) last_attack_time = game_time;
  if(std::ranges::count(reset_attack_spells, spell_cast->name())) last_attack_time = -FLT_MAX;
  // PrintMessage(0xFFFFFF, std::format("{:x}", (uintptr_t)spell_cast));
  // PrintMessage(0xFFFFFF, std::format("{:x}", spell_cast->slot()));

  // PrintMessage(0xFFFFFF, std::format("{}", spell_cast->name()));
}

void script::update() {
  game_time = GameTime();

  check_orb_state();
  check_marked_object();

  Draw([&] {
    if(config::inst().show_attack_range) Circle(self->position(), real_range(), 0xffffffff, 1.5f);
    if(markedObject && markedObject->IsAlive() && markedObject->visible()) {
      Circle(markedObject->position(), markedObject->BonusRadius(), 0xff0c9d00, 4.5f);
    }
  });

  if(!CanSendInput()) return;

  if(orbState != OrbState::Off) {
    if(is_reloading()) idle();
    else attack();
  }
}

bool script::can_attack() { return self->state() & CanAttack; }

bool script::can_do_action() {
  if(game_time < last_action_time + interval) return false;
  last_action_time = game_time;
  return true;
}

bool script::is_reloading() { return game_time < last_attack_time + self->AttackDelay() - 0.1f; }

bool script::is_attacking() { return game_time < last_attack_time + self->AttackWindup() - 0.1f; }

void script::idle() {
  if(!is_attacking() && can_do_action()) Move2Mouse();
}

void script::attack() {
  if(const auto obj = get_target(real_range(), true); obj && can_attack() && can_do_action()) {
    AttackObject(obj);
  } else idle();
}

float script::real_range() { return self->attack_range() + self->BonusRadius(); }

void script::check_marked_object() {
  if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    if(const auto obj = *objUnderMouse; obj->IsHero() && obj->IsEnemy()) markedObject = obj;
  }
}

void script::check_orb_state() {
  if(ImGui::IsKeyDown(config::inst().kite_key)) orbState = OrbState::Kite;
  else if(ImGui::IsKeyDown(config::inst().clean_key)) orbState = OrbState::Clear;
  else orbState = OrbState::Off;
}

Object *script::get_target(float range, bool collision) {
  if(orbState == OrbState::Kite) {
    if(std::ranges::count(heros->objects_in_range(range, collision), markedObject)) return markedObject;
    return heros->best_object_in_range(range, collision);
  }
  if(orbState == OrbState::Clear) {
    auto target = minions->best_object_in_range(range, collision);
    if(!target) target = turrets->best_object_in_range(range, collision);
    if(!target) target = inhibs->best_object_in_range(range, collision);
    return target;
  }
  return nullptr;
}

bool script::has_buff(std::string_view name) {
  return std::ranges::any_of(self->buffs(), [name, this](Buff *buff) {
    return buff->name() == name && buff->starttime() <= game_time && buff->endtime() >= game_time;
  });
}