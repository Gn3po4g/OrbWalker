#include "pch.hpp"

#include "script.hpp"

#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"

std::map<std::string_view, Script *> scripts{
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

void Script::update() {
  game_time = function::GameTime();
  check_orb_state();
  check_marked_object();
  extra_update();

  if(!function::CanSendInput()) return;

  if(orbState != OrbState::Off) {
    if(is_reloading()) idle();
    else attack();
  }
}

float Script::draw_range() { return self->RealAttackRange(); }

void Script::extra_update() {
  static SpellCast *last_spell_cast{};
  const auto spell_cast = self->spell_cast();
  if(spell_cast && (spell_cast->type() == -1 || spell_cast->id() >= 14) && spell_cast != last_spell_cast) {
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
  auto obj = get_target(draw_range(), true);
  if(obj && can_attack() && can_do_action()) {
    function::AttackObject(obj);
  } else idle();
}

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
    return buff->name() == name && buff->starttime() <= game_time && buff->endtime() >= game_time && buff->count_alt()
        && buff->count();
  });
}

bool get_buff(std::string_view name) {
  static std::map<std::string_view, float> last_time;
  for(auto buff : self->buffs()) {
    if(buff->name() != name) continue;
    if(buff->starttime() > last_time[name]) {
      last_time[name] = buff->starttime();
      return true;
    }
  }
  return false;
}

void Ashe::extra_update() {
  if(get_buff("AsheQAttack")) last_attack_time = -FLT_MAX;
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
  auto obj = get_target(draw_range(), false);
  if(obj && !obj->IsBuilding() && can_attack() && can_do_action()) {
    function::CastSpell(obj, 2);
  } else idle();
}

float Cassiopeia::draw_range() { return 700.f; }

bool Graves::is_reloading() { return game_time < last_attack_time + self->AttackDelay() * .15f - .09f; }

bool Kaisa::can_attack() { return Script::can_attack() && !has_buff("KaisaE"); }

void Vayne::extra_update() {
  if(get_buff("vaynetumblebonus")) last_attack_time = -FLT_MAX;
  Script::extra_update();
}

bool Zeri::can_attack() { return self->state() & CharacterState::CanCast; }

bool Zeri::is_reloading() { return game_time < self->GetSpell(0)->readyTime() - interval; }

void Zeri::attack() {
  auto obj = get_target(draw_range(), false);
  if(obj && can_attack() && can_do_action()) function::CastSpell(obj->position(), 0);
  else idle();
}

float Zeri::draw_range() { return self->RealAttackRange() - self->BonusRadius() + 250.f; }