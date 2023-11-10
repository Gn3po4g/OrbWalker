#include "pch.hpp"

#include "script.hpp"

#include "champion/akshan.hpp"
#include "champion/aphelios.hpp"
#include "champion/azir.hpp"
#include "champion/caitlyn.hpp"
#include "champion/cassiopeia.hpp"
#include "champion/graves.hpp"
#include "champion/kaisa.hpp"
#include "champion/sett.hpp"
#include "champion/zeri.hpp"
#include "config/config.hpp"
#include "memory/function.hpp"

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
    case "Cassiopeia"_FNV:
      return instance_.reset(new Cassiopeia);
    case "Graves"_FNV:
      return instance_.reset(new Graves);
    case "Kaisa"_FNV:
      return instance_.reset(new Kaisa);
    case "Sett"_FNV:
      return instance_.reset(new Sett);
    case "Zeri"_FNV:
      return instance_.reset(new Zeri);
    default:
      return instance_.reset(new script);
    }
  });
  return *instance_;
}

void script::update() {
  game_time = GameTime();

  check_orb_state();
  check_marked_object();

  Draw([&] {
    if (config::inst().show_attack_range) Circle(Object::self()->position(), real_range(), 0xffffffff, 1.5f);
    if (markedObject && markedObject->IsAlive() && markedObject->visible()) {
      Circle(markedObject->position(), markedObject->BonusRadius(), 0xff0c9d00, 3.0f);
    }
  });

  if (!CanSendInput()) return;

  if (orbState != OrbState::Off) {
    if (is_reloading()) idle();
    else attack();
  }

  // if (ImGui::IsKeyPressed(ImGuiKey_V)) {
  //   uptr target  = RVA(oWorldToScreen);
  //   bool found   = false;
  //   auto base    = Read<uintptr_t>(RVA(oViewPort));
  //   auto vtable = *(uptr **)base;
  //   size_t index{};
  //   while (!found && !IsBadCodePtr((FARPROC)vtable[index])) {
  //     if (vtable[index] == target) {
  //       PrintMessage<0xFFFFFF>("found at: {}", index);
  //       found = true;
  //     }
  //     index++;
  //   }
  //   if (!found) PrintMessage<0xFFFFFF>("not found");
  // }
}

void script::run(SpellCast *spell_cast, Object *obj) {
  last_cast_spell = spell_cast->name();
  if (spell_cast->is_attack()) last_attack_time = game_time - 0.1f;
  if (spell_cast->is_attack_reset()) last_attack_time = -FLT_MAX;
  PrintMessage<0xFFFFFF>("name: {}", spell_cast->name());
  // auto addr = *(void **)(*(uintptr_t *)spell_cast + 0x60);
  //  if (spell_cast->name() == "SivirW")
  //  MessageBoxA(nullptr, std::format("{:x}", (uintptr_t)spell_cast).c_str(), "", MB_OK);
}

bool script::can_attack() { return Object::self()->state() & CanAttack; }

bool script::can_do_action() {
  if (game_time < last_action_time + interval) return false;
  last_action_time = game_time;
  return true;
}

bool script::is_reloading() { return game_time < last_attack_time + Object::self()->AttackDelay(); }

bool script::is_attacking() { return game_time < last_attack_time + Object::self()->AttackWindup() + 0.1f; }

void script::idle() {
  if (!is_attacking() && can_do_action()) Move2Mouse();
}

void script::attack() {
  if (const auto obj = get_attack_target(); obj && can_attack() && can_do_action()) {
    AttackObject(obj);
  } else idle();
}

float script::real_range() { return Object::self()->attack_range() + Object::self()->BonusRadius(); }

void script::check_marked_object() {
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    if (const auto obj = Object::obj_under_mouse(); obj && obj->compare_type_flags(Hero) && obj->IsEnemy())
      markedObject = obj;
  }
}

void script::check_orb_state() {
  if (ImGui::IsKeyDown(config::inst().kite_key)) orbState = OrbState::Kite;
  else if (ImGui::IsKeyDown(config::inst().clean_key)) orbState = OrbState::Clear;
  else orbState = OrbState::Off;
}

Object *script::get_attack_target() {
  if (orbState == OrbState::Kite) {
    return ObjList::get_in_order(
      Hero, [&](Object *obj) { return in_attack_range(obj); }, markedObject
    );
  }
  if (orbState == OrbState::Clear) {
    return ObjList::get_in_order(Minion | Building, [&](Object *obj) { return in_attack_range(obj); });
  }
  return nullptr;
}

Object *script::get_skill_target(float range) {
  if (orbState == OrbState::Kite) {
    return ObjList::get_in_order(
      Hero, [&](Object *obj) { return in_skill_range(obj, range); }, markedObject
    );
  }
  if (orbState == OrbState::Clear) {
    return ObjList::get_in_order(Minion, [&](Object *obj) { return in_skill_range(obj, range); });
  }
  return nullptr;
}

bool script::has_buff(Object *obj, std::string_view name) {
  return std::ranges::any_of(obj->buffs(), [name, this](Buff *buff) {
    return buff->is_valid() && game_time >= buff->starttime() && game_time <= buff->endtime() && buff->name() == name;
  });
}

bool script::in_attack_range(Object *obj) {
  return obj->position() - Object::self()->position()
      <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius();
}

bool script::in_skill_range(Object *obj, float range) { return obj->position() - Object::self()->position() <= range; }
