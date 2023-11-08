#include "pch.hpp"

#include "config.hpp"

#include "class/obj_list.hpp"
#include "class/object.hpp"

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
  current_skin      = config_json.value(Object::self()->name() + ".current_skin", 0);
  show_attack_range = config_json.value("show_attack_range", true);
  kite_key          = config_json.value("kite_key", ImGuiKey_Space);
  clean_key         = config_json.value("clean_key", ImGuiKey_V);
  prev_skin_key     = config_json.value("prev_skin_key", ImGuiKey_PageUp);
  next_skin_key     = config_json.value("next_skin_key", ImGuiKey_PageDown);
  menu_key          = config_json.value("menu_key", ImGuiKey_Insert);
  selector          = config_json.value("selector", health_lowest);
  in.close();
}

void config::save() {
  auto out = std::ofstream(file_name);
  if (!out.good()) return;
  config_json[Object::self()->name() + ".current_skin"] = current_skin;
  config_json["show_attack_range"]                      = show_attack_range;
  config_json["kite_key"]                               = kite_key;
  config_json["clean_key"]                              = clean_key;
  config_json["prev_skin_key"]                          = prev_skin_key;
  config_json["next_skin_key"]                          = next_skin_key;
  config_json["menu_key"]                               = menu_key;
  config_json["selector"]                               = selector;
  out << config_json.dump(2);
  out.close();
}