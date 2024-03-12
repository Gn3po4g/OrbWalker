#pragma once

class config {
public:
  static config &inst();

  bool show_attack_range;
  bool show_click;
  Selector selector;
  ImGuiKey kite_key;
  ImGuiKey clean_key;
  ImGuiKey reset_key;

  ImGuiKey menu_key;

  void save();

private:
  config();
  inline static std::unique_ptr<config> instance_;
};