#pragma once

class HudMouse : public IMEMBER {
public:
  screen_pos &mouse_screen_pos();
  vec3 &mouse_last_world();
};
class HudOrder {};
class HudCast {};

class Hud : public IMEMBER {
public:
  static Hud &inst();
  HudMouse *hud_mouse();
  HudOrder *hud_order();
  HudCast *hud_cast();
  bool is_background();
  bool &is_champion_only();

private:
  inline static std::unique_ptr<Hud> instance_;
};