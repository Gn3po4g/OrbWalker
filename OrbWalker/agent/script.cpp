#include "pch.hpp"

#include "config.hpp"
#include "script.hpp"

#include "champion/aphelios.hpp"
#include "champion/azir.hpp"
#include "champion/caitlyn.hpp"
#include "champion/cassiopeia.hpp"
#include "champion/graves.hpp"
#include "champion/kalista.hpp"
#include "champion/sett.hpp"
#include "champion/zeri.hpp"

class Akshan : public script {
  bool is_attacking() override { return game_time < last_attack_time + Object::self()->AttackWindup() * 1.75 + 0.175; }
};

script &script::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] {
    switch (FNV(Object::self()->name())) {
    case "Akshan"_FNV:
      return instance_.reset(new Akshan);
    case "Aphelios"_FNV:
      return instance_.reset(new Aphelios);
    case "Azir"_FNV:
      return instance_.reset(new Azir);
    case "Caitlyn"_FNV:
      return instance_.reset(new Caitlyn);
    // case "Cassiopeia"_FNV:
    //   return instance_.reset(new Cassiopeia);
    case "Graves"_FNV:
      return instance_.reset(new Graves);
    case "Kalista"_FNV:
      return instance_.reset(new Kalista);
    case "Sett"_FNV:
      return instance_.reset(new Sett);
    // case "Zeri"_FNV:
    //   return instance_.reset(new Zeri);
    default:
      return instance_.reset(new script);
    }
  });
  return *instance_;
}

void script::update() {
  game_time = ::game_time();

  check_orb_state();
  check_marked_object();

  Draw([&] {
    if (config::inst().show_attack_range) Circle(Object::self()->position(), real_range(), 0xFFFFFFFF, 1.5f);
    if (markedObject && markedObject->IsAlive() && markedObject->visible()) {
      Circle(markedObject->position(), markedObject->BonusRadius(), 0xFF33AB84, 4.5f);
    }
  });

  if (!Object::self()->IsAlive() || Chat::inst().is_open() || Hud::inst().is_background()) return;

  if (orbState != OrbState::Off) {
    if (is_reloading()) idle();
    else attack();
  }
}

void script::run(SpellCast *spell_cast, Object *obj) {
  last_cast_spell = spell_cast->name();
  if (spell_cast->is_attack()) last_attack_time = game_time;
  if (spell_cast->is_attack_reset()) last_attack_time = -FLT_MAX;
  // PrintMessage<0xFFFFFF>("addr: {}", spell_cast->name());
}

bool script::can_attack() { return Object::self()->state() & CanAttack && !Object::self()->IsCasting(); }

bool script::is_reloading() { return game_time < last_attack_time + Object::self()->AttackDelay() - ping() * 2; }

bool script::is_attacking() { return game_time < last_attack_time + Object::self()->AttackWindup(); }

void script::idle() {
  if (!is_attacking()) do_action(Move2Mouse);
}

void script::attack() {
  if (const auto obj = get_attack_target(); obj && can_attack()) {
    do_action(std::bind(AttackObject, obj));
  } else idle();
}

float script::real_range() { return Object::self()->attack_range() + Object::self()->BonusRadius(); }

void script::do_action(std::function<void()> fun) {
  constexpr float interval = 1.f / 20;
  static float last_action_time{-FLT_MAX};
  if (game_time > last_action_time + interval) {
    last_action_time = game_time;
    fun();
  }
};

void script::check_marked_object() {
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    if (const auto obj = Object::obj_under_mouse(); obj && obj->type() == Hero && obj->IsEnemy()) markedObject = obj;
  }
  if (ImGui::IsKeyPressed(config::inst().reset_key)) markedObject = nullptr;
}

void script::check_orb_state() {
  if (ImGui::IsKeyDown(config::inst().kite_key)) {
    orbState                       = OrbState::Kite;
    Hud::inst().is_champion_only() = true;
  } else if (ImGui::IsKeyDown(config::inst().clean_key)) orbState = OrbState::Clear;
  else orbState = OrbState::Off;

  if (ImGui::IsKeyReleased(config::inst().kite_key)) Hud::inst().is_champion_only() = false;
}

Object *script::get_attack_target() {
  if (orbState == OrbState::Kite) {
    return ObjList::get_object_in(
      {Hero}, [&](Object *obj) { return in_attack_range(obj); }, markedObject
    );
  }
  if (orbState == OrbState::Clear) {
    return ObjList::get_object_in({Minion, Turret, Inhibitor}, [&](Object *obj) { return in_attack_range(obj); });
  }
  return nullptr;
}

Object *script::get_skill_target(float range) {
  if (orbState == OrbState::Kite) {
    return ObjList::get_object_in(
      {Hero}, [&](Object *obj) { return in_skill_range(obj, range); }, markedObject
    );
  }
  if (orbState == OrbState::Clear) {
    return ObjList::get_object_in({Minion}, [&](Object *obj) { return in_skill_range(obj, range); });
  }
  return nullptr;
}

bool script::in_attack_range(Object *obj) {
  return distance(obj->position(), Object::self()->position())
      <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius();
}

bool script::in_skill_range(Object *obj, float range) {
  return distance(obj->position(), Object::self()->position()) <= range;
}
