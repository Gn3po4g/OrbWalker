#include "pch.hpp"

#include "config.hpp"

#include "agent/ui.hpp"
#include "class/object.hpp"

using namespace nlohmann;

std::string file_name = "setting.json"s;
json config_json      = json::object();

config &config::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(new config); });
  return *instance_;
}

config::config() {
  auto in = std::ifstream(file_name);
  if (in.good()) {
    const json j = json::parse(in, nullptr, false, true);
    if (!j.is_discarded()) config_json = j;
  }
  ImGuiKey temp_key = ImGuiKey( - 1);
  current_skin      = config_json.value(json::json_pointer("/skin/" + Object::self()->name()), 0);
  show_attack_range = config_json.value("show_attack_range", true);
  show_click        = config_json.value("show_click", true);
  selector          = config_json.value("selector", HealthLowest);
  temp_key          = config_json.value("kite_key", ImGuiKey(-1));
  kite_key          = keyMap.contains(temp_key) ? temp_key : ImGuiKey_Space;
  temp_key          = config_json.value("clean_key", ImGuiKey(-1));
  clean_key         = keyMap.contains(temp_key) ? temp_key : ImGuiKey_V;
  temp_key          = config_json.value("reset_key", ImGuiKey(-1));
  reset_key         = keyMap.contains(temp_key) ? temp_key : ImGuiKey_Tab;
  temp_key          = config_json.value("prev_skin_key", ImGuiKey(-1));
  prev_skin_key     = keyMap.contains(temp_key) ? temp_key : ImGuiKey_PageUp;
  temp_key          = config_json.value("next_skin_key", ImGuiKey(-1));
  next_skin_key     = keyMap.contains(temp_key) ? temp_key : ImGuiKey_PageDown;
  temp_key          = config_json.value("menu_key", ImGuiKey(-1));
  menu_key          = keyMap.contains(temp_key) ? temp_key : ImGuiKey_Insert;
  in.close();
}

void config::save() {
  auto out = std::ofstream(file_name);
  if (!out.good()) return;
  config_json["skin"][Object::self()->name()] = current_skin;
  config_json["show_attack_range"]            = show_attack_range;
  config_json["show_click"]                   = show_click;
  config_json["kite_key"]                     = kite_key;
  config_json["clean_key"]                    = clean_key;
  config_json["reset_key"]                    = reset_key;
  config_json["prev_skin_key"]                = prev_skin_key;
  config_json["next_skin_key"]                = next_skin_key;
  config_json["menu_key"]                     = menu_key;
  config_json["selector"]                     = selector;
  out << config_json.dump(2);
  out.close();
}