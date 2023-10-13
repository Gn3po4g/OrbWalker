#pragma once

enum selector : int { health_lowest, distance_closest, count };

class config {
public:
  static config &inst();

  bool show_attack_range;
  int selector;
  ImGuiKey kite_key;
  ImGuiKey clean_key;

  int current_skin;
  ImGuiKey prev_skin_key;
  ImGuiKey next_skin_key;

  ImGuiKey menu_key;

  void save();

private:
  config();
  inline static std::unique_ptr<config> instance_;
};