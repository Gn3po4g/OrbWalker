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
       {"prev_skin_key", cfg.prev_skin_key},
       {"next_skin_key", cfg.next_skin_key},
     }                   },
    {"skin",    cfg.skins}
  };
}

void from_json(const json &j, ImGuiKey &key) {
  const auto k = (ImGuiKey)j.get<int>();
  if (keyMap.contains(k)) key = k;
  else key = ImGuiKey_None;
}

void from_json(const json &j, config &cfg) {
  j.at("skin").get_to(cfg.skins);
  j.at("general").at("show_attack_range").get_to(cfg.show_attack_range);
  j.at("general").at("show_click").get_to(cfg.show_click);
  j.at("general").at("selector").get_to(cfg.selector);
  j.at("key").at("menu_key").get_to(cfg.menu_key);
  j.at("key").at("kite_key").get_to(cfg.kite_key);
  j.at("key").at("clean_key").get_to(cfg.clean_key);
  j.at("key").at("reset_key").get_to(cfg.reset_key);
  j.at("key").at("prev_skin_key").get_to(cfg.prev_skin_key);
  j.at("key").at("next_skin_key").get_to(cfg.next_skin_key);
}

config &config::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [] {
    try {
      instance_.reset(new config);
      std::ifstream file(file_name);
      json::parse(file).get_to(*instance_);
      file.close();
      instance_->current_skin = instance_->skins[Object::self()->name()];
    } catch (...) { instance_.reset(new config); }
  });
  return *instance_;
}

config::config()
    : skins({}), show_attack_range(true), show_click(true), selector(HealthLowest), kite_key(ImGuiKey_Space),
      clean_key(ImGuiKey_V), reset_key(ImGuiKey_Tab), current_skin(0), prev_skin_key(ImGuiKey_PageUp),
      next_skin_key(ImGuiKey_PageDown), menu_key(ImGuiKey_Insert) {}

void config::save() {
  skins[Object::self()->name()] = current_skin;
  std::ofstream file(file_name);
  file << json(*this).dump(2);
  file.close();
}