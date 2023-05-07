#include "pch.h"

struct Timer {
  float last_attack_time{};
  float next_move_time{};
};

namespace OrbWalker {
  Object* me{};
  ObjList* heroes{};
  ObjList* minions{};
  ObjList* turrets{};
  ObjList* inhibitors{};
  uintptr_t hud_input{};
  XMFLOAT3* mouse_pos{};
  bool* p_aco;

  void Initialize() {
    me = *(Object**)offsets.oLocalPlayer;
    heroes = *(ObjList**)offsets.oHeroList;
    turrets = *(ObjList**)offsets.oTurretList;
    //inhibitors = *(ObjList**)offsets.oInhibitorList;
    minions = *(ObjList**)offsets.oMinionList;
    hud_input = *(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x48);
    mouse_pos = (XMFLOAT3*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x28) + 0x20);
    p_aco = (bool*)(*(uintptr_t*)(*(uintptr_t*)offsets.oHudInstance + 0x60) + 0x30);
    while (Functions::GetGameTime() < 1.f) {}
    Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends OrbWalker", 0xFFFFFF);
  }

  Object* GetTarget(const Type type) {
    Object* target = nullptr;
    if (type == Type::AutoKite) {
      target = heroes->get_lowest_health(me);
    }
    else if (type == Type::CleanLane) {
      target = minions->get_lowest_health(me);
      if (target == nullptr) {
        target = turrets->get_lowest_health(me);
      }
    }
    else if (type == Type::LastHit) {
      target = minions->get_last_hit(me);
    }
    return target;
  }

  void Attack(Object const* obj) {
    static float next = 0.f;
    const float now = Functions::GetGameTime();
    if (now < next) return;
    next = now + .033f;
    const auto pos = Renderer::WorldToScreen(obj->position());
    Functions::IssueOrder(hud_input, 0, 0, 1, pos.x, pos.y, 1);
  }
  void Move() {
    static float next = 0.f;
    const float now = Functions::GetGameTime();
    if (now < next) return;
    next = now + .033f;
    const auto pos = Renderer::WorldToScreen(*mouse_pos);
    INPUT input = {};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(INPUT));
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
    SendInput(1, &input, sizeof(input));
  }

  void Execute(const Type& type) {
    static Timer timer{};
    static bool is_turning_around = false;
    const float now = Functions::GetGameTime();
    if (Functions::IsChatOpen() || Functions::IsLeagueInBackground()) return;
    if (const auto target = GetTarget(type); target && (now >= timer.last_attack_time + me->ad() || is_turning_around))    {
      if (!is_turning_around) timer.last_attack_time = now;
      is_turning_around = true;
      Attack(target);
      if (me->IsFacing(target)) {
        is_turning_around = false;
        timer.next_move_time = now + me->acd();
      }
    }
    else if (now >= timer.next_move_time) {
      Move();
    }
  }
}
