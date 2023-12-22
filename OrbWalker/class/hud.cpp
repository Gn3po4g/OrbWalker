#include "pch.hpp"

#include "hud.hpp"
#include "memory/offset.hpp"

Hud &Hud::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(Read<Hud *>(RVA(oHudInstance))); });
  return *instance_;
}

HudMouse *Hud::hud_mouse() { return MEMBER<HudMouse *>(0x28); }

HudOrder *Hud::hud_order() { return MEMBER<HudOrder *>(0x48); }

HudCast *Hud::hud_cast() { return MEMBER<HudCast *>(0x68); }

bool Hud::is_background() { return MEMBER<bool>(0xB9); }

bool &Hud::is_champion_only() { return Read<bool>(MEMBER<uptr>(0x60) + 0x30); }

screen_pos &HudMouse::mouse_screen_pos() {
  const auto mouse = Read<uptr>(RVA(oMouseScreenPos));
  return Read<screen_pos>(mouse + 0xC);
}

vec3 &HudMouse::mouse_last_world() { return MEMBER<vec3>(0x38); }
