#include "pch.h"

struct Timer {
  duration<float> last_attack_time{};
  duration<float> next_move_time{};
};

namespace OrbWalker {
  Object* me{};
  ObjList* heroes{};
  ObjList* minions{};
  ObjList* turrets{};
  //ObjList* inhibitors{};
  uintptr_t hud_input{};
  bool* p_aco;

  void Initialize() {
    Functions::Initialize();
    Renderer::Initialize();
    me = *(Object**)offsets.oLocalPlayer;
    heroes = *(ObjList**)offsets.oHeroList;
    turrets = *(ObjList**)offsets.oTurretList;
    //inhibitors = *(ObjList**)offsets.oInhibitorList;
    minions = *(ObjList**)offsets.oMinionList;
    hud_input = *(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x48);
    p_aco = (bool*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x60) + 0x30);
    while (*(float*)offsets.oGameTime < .5f) std::this_thread::sleep_for(250ms);
    Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends OrbWalker", 0xFFFFFF);
  }

  Object* GetTarget(const Type type) {
    Object* target = nullptr;
    if (type == Type::AutoKite) {
      target = heroes->GetLowestHealth(me, false);
    }
    if (type == Type::CleanLane) {
      target = minions->GetLowestHealth(me, true);
      if (target == nullptr) {
        target = turrets->GetLowestHealth(me, false);
      }
    }
    return target;
  }

  void Attack(Object const* obj) {
    const auto pos = Renderer::WorldToScreen(obj->position());
    Functions::IssueOrder(hud_input, 0, 0, 1, pos.x, pos.y, 0);
  }

  void Move() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
  }

  void Execute(const Type& type) {
    static Timer timer{};
    static auto next = duration<float>(*(float*)offsets.oGameTime);
    const auto now = duration<float>(*(float*)offsets.oGameTime);
    if (Functions::IsChatOpen() || Functions::IsLeagueInBackground() || now < next) return;
    next = now + milliseconds(33);
    if (const auto target = GetTarget(type); target && now >= timer.last_attack_time + me->ad()) {
      timer.last_attack_time = now;
      timer.next_move_time = now + me->acd();
      last_object = target;
      Attack(target);
    }
    else if (now >= timer.next_move_time) Move();
  }
}
