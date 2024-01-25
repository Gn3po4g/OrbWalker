#include "pch.hpp"

#include "config.hpp"

#include "agent/ui.hpp"
#include "class/object.hpp"

using namespace nlohmann;

constexpr auto file_name = "setting.json"s;

void to_json(json &j, const config &cfg) {
  j = json{
    {"general",
     {
       {"show_attack_range", cfg.show_attack_range},
       {"show_click", cfg.show_click},
       {"selector", cfg.selector},
     }                   },
    {"key",
     {
       {"menu_key", cfg.menu_key},
       {"kite_key", cfg.kite_key},
       {"clean_key", cfg.clean_key},
       {"reset_key", cfg.reset_key},
     }                   },
  };
}

void from_json(const json &j, ImGuiKey &key) {
  const auto k = (ImGuiKey)j.get<int>();
  if (keyMap.contains(k)) key = k;
  else key = ImGuiKey_None;
}

void from_json(const json &j, config &cfg) {
  j.at("general").at("show_attack_range").get_to(cfg.show_attack_range);
  j.at("general").at("show_click").get_to(cfg.show_click);
  j.at("general").at("selector").get_to(cfg.selector);
  j.at("key").at("menu_key").get_to(cfg.menu_key);
  j.at("key").at("kite_key").get_to(cfg.kite_key);
  j.at("key").at("clean_key").get_to(cfg.clean_key);
  j.at("key").at("reset_key").get_to(cfg.reset_key);
}

config &config::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [] {
    try {
      instance_.reset(new config);
      std::ifstream file(file_name);
      json::parse(file).get_to(*instance_);
      file.close();
    } catch (...) { instance_.reset(new config); }
  });
  return *instance_;
}

config::config()
    : show_attack_range(true), show_click(true), selector(HealthLowest), kite_key(ImGuiKey_Space),
      clean_key(ImGuiKey_V), reset_key(ImGuiKey_Tab), menu_key(ImGuiKey_Insert) {}

void config::save() {
  std::ofstream file(file_name);
  file << json(*this).dump(2);
  file.close();
}