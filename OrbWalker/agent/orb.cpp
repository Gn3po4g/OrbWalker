#include "pch.hpp"

#include "orb.hpp"

#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"
#include "memory/offset.hpp"

std::map<std::string_view, Script *> scripts{
  //{"Ashe",       new Ashe()      },
  //{"Cassiopeia", new Cassiopeia()},
  {"Graves",     new Graves()    },
  {"Kaisa",      new Kaisa()     },
  {"Zeri",       new Zeri()      }
};

Orb *orb;

Orb::Orb()
    : markedObject(nullptr), orbState(OrbState::Off),
      script(scripts.contains(self->name()) ? scripts[self->name()] : new Script()) {}

void Orb::check_marked_object() {
  if(markedObject && (!markedObject->IsAlive() || !markedObject->visible())) { markedObject = nullptr; }
  if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    auto obj = *objUnderMouse;
    if(obj->IsHero() && obj->IsEnemy()) {
      markedObject = obj;
    } else {
      markedObject = nullptr;
    }
  }
}

void Orb::check_orb_state() {
  if(ImGui::IsKeyDown(config::kiteKey)) {
    orbState = OrbState::Kite;
  } else if(ImGui::IsKeyDown(config::cleanKey)) {
    orbState = OrbState::Clear;
  } else {
    orbState = OrbState::Off;
  }
}

void Orb::update() {
  check_orb_state();
  check_marked_object();
  script->update();

  if(!function::CanSendInput()) return;

  if(orbState != OrbState::Off) {
    if(script->is_reloading()) script->idle();
    else script->attack();
  }
}