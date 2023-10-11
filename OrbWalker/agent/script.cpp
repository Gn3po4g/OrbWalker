#include "pch.hpp"

#include "champion/all.hpp"
#include "script.hpp"

#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"

std::map<std::string_view, Script *> scripts{
  {"Aphelios",   new Aphelios()  },
  {"Ashe",       new Ashe()      },
  {"Cassiopeia", new Cassiopeia()},
  {"Graves",     new Graves()    },
  {"Kaisa",      new Kaisa()     },
  {"Vayne",      new Vayne()     },
  {"Zeri",       new Zeri()      }
};

Script *script;

void LoadScript() {
  if(scripts.contains(self->name())) script = scripts[self->name()];
  else script = new Script();
}

void Script::run(SpellCast *spell_cast, Object *obj) {
  std::string name = *(RiotString16 *)(*(uintptr_t *)spell_cast + 0x28);
  std::vector<std::string> attack_spells{
    "CaitlynPassiveMissile", "LucianPassiveAttack", "KogMawBioArcaneBarrageAttack", "SivirWAttack",
    "TwitchSprayAndPrayAttack","XayahPassiveAttack"};
  if(spell_cast->type() == -1 || std::ranges::count(attack_spells, name)) last_attack_time = game_time;
   PrintMessage(0xFFFFFF, std::format("{}", name));
  //  PrintMessage(0xFFFFFF, std::format("{:x}\t{:x}", spell_cast->id(), spell_cast->type()));
  //   uint16_t id = *(uint16_t *)((uintptr_t)a3 + 0x11C);
  //   int32_t type = *(int32_t *)((uintptr_t)a3 + 0x8);
  //      FLOAT3 start = *(FLOAT3 *)((uintptr_t)a3 + 0xA4);
  //      FLOAT3 end = *(FLOAT3 *)((uintptr_t)a3 + 0xB0);
}

void Script::update() {
  game_time = GameTime();

  check_orb_state();
  check_marked_object();

  Draw([&]() {
    if(config::showAttackRange) Circle(self->position(), real_range(), 0xffffffff, 1.5f);
    if(markedObject) Circle(markedObject->position(), markedObject->BonusRadius(), 0xff0c9d00, 5.f);
  });

  if(!CanSendInput()) return;

  if(orbState != OrbState::Off) {
    if(is_reloading()) idle();
    else attack();
  }
}

bool Script::can_attack() { return self->state() & CharacterState::CanAttack; }

bool Script::can_do_action() {
  if(game_time < last_action_time + interval) return false;
  last_action_time = game_time;
  return true;
}

bool Script::is_reloading() { return game_time < last_attack_time + self->AttackDelay(); }

bool Script::is_attacking() { return game_time < last_attack_time + self->AttackWindup() /* - .03f*/; }

void Script::idle() {
  if(!is_attacking() && can_do_action()) Move2Mouse();
}

void Script::attack() {
  auto obj = get_target(real_range(), true);
  if(obj && can_attack() && can_do_action()) {
    AttackObject(obj);
  } else idle();
}

float Script::real_range() { return self->attack_range() + self->BonusRadius(); }

void Script::check_marked_object() {
  if(markedObject && (!markedObject->IsAlive() || !markedObject->visible())) { markedObject = nullptr; }
  if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    auto obj = *objUnderMouse;
    if(obj->IsHero() && obj->IsEnemy()) markedObject = obj;
    else markedObject = nullptr;
  }
}

void Script::check_orb_state() {
  if(ImGui::IsKeyDown(config::kiteKey)) orbState = OrbState::Kite;
  else if(ImGui::IsKeyDown(config::cleanKey)) orbState = OrbState::Clear;
  else orbState = OrbState::Off;
}

Object *Script::get_target(float range, bool collision) {
  if(orbState == OrbState::Kite) {
    if(std::ranges::count(heros->objects_in_range(range, collision), markedObject)) return markedObject;
    else return heros->best_object_in_range(range, collision);
  } else if(orbState == OrbState::Clear) {
    auto target = minions->best_object_in_range(range, collision);
    if(!target) target = turrets->best_object_in_range(range, collision);
    if(!target) target = inhibs->best_object_in_range(range, collision);
    return target;
  } else {
    return nullptr;
  }
}

bool Script::has_buff(std::string_view name) {
  return std::ranges::any_of(self->buffs(), [name, this](Buff *buff) {
    return buff->name() == name && buff->starttime() <= game_time && buff->endtime() >= game_time;
  });
}