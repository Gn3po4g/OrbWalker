#include "pch.hpp"

#include "config.hpp"

#include "agent/orb.hpp"

namespace config {
std::string fileName = "setting.json"s;
json configJson = json();

void Load() {
  const auto self = orb->self;
  auto in = std::ifstream(fileName);
  if(!in.good()) return;

  if(json j = json::parse(in, nullptr, false, true); j.is_discarded()) return;
  else configJson = j;

  if(self) currentSkin = configJson.value(self->dataStack()->baseSkin.model + ".currentSkinIndex", 0);
  showAttackRange = configJson.value("showAttackRange", true);
  kiteKey = configJson.value("kiteKey", ImGuiKey_Space);
  cleanKey = configJson.value("cleanKey", ImGuiKey_V);
  prevSkinKey = configJson.value("prevSkinKey", ImGuiKey_PageUp);
  nextSkinKey = configJson.value("nextSkinKey", ImGuiKey_PageDown);
  menuKey = configJson.value("menuKey", ImGuiKey_Insert);
  targeting = configJson.value("targeting", Targeting::health_lowest);
  in.close();
}

void Save() {
  const auto self = orb->self;
  auto out = std::ofstream(fileName);
  if(!out.good()) return;
  if(self) {
    configJson[self->dataStack()->baseSkin.model + ".currentSkinIndex"] = currentSkin;
    configJson["showAttackRange"] = showAttackRange;
    configJson["kiteKey"] = kiteKey;
    configJson["cleanKey"] = cleanKey;
    configJson["prevSkinKey"] = prevSkinKey;
    configJson["nextSkinKey"] = nextSkinKey;
    configJson["menuKey"] = menuKey;
    configJson["targeting"] = targeting;
  }
  out << configJson.dump();
  out.close();
}
} // namespace config