#include "stdafx.hpp"

#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/offset.hpp"
#include "orb.hpp"

Orb *orb;

Orb::Orb()
    : self(*(Object **)offset->oLocalPlayer), heros(*(ObjList **)offset->oHeroList),
      minions(*(ObjList **)offset->oMinionList), turrets(*(ObjList **)offset->oTurretList), script(new Script()),
      markedObject(nullptr), orbState(OrbState::Off) {
  if(scripts.contains(self->name().str)) script = scripts[self->name().str];
}

void Orb::check_marked_object() {
  if(markedObject && (!markedObject->IsAlive() || !markedObject->visible())) { markedObject = nullptr; }
  if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    auto obj = *(Object **)(*(uintptr_t *)(offset->oObjUnderMouse) + 0x18);
    if(heros->Contains(obj) && obj->IsEnemy()) {
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