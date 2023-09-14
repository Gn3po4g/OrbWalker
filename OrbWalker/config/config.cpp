#include "stdafx.hpp"

namespace config {
  json configJson = json();

  bool showMenu{true};

   bool showAttackRange{true};
  int targeting{};
  ImGuiKey kiteKey{ImGuiKey_Space};
  ImGuiKey cleanKey{ImGuiKey_V};

  int currentSkin{};
  ImGuiKey prevSkinKey{ImGuiKey_PageUp};
  ImGuiKey nextSkinKey{ImGuiKey_PageDown};

  ImGuiKey menuKey{ImGuiKey_Insert};

  void Load() {
    const auto self = script::self;
    auto in = std::ifstream("setting");
    if(!in.good()) {
      return;
    }
    if(json j = json::parse(in, nullptr, false, true); j.is_discarded()) {
      return;
    } else {
      configJson = j;
    }
    if(self) {
      currentSkin = configJson.value(std::string(self->dataStack()->baseSkin.model.str) + ".currentSkinIndex", 0);
    }
    showAttackRange = configJson.value("showAttackRange", true);
    kiteKey = configJson.value("kiteKey", ImGuiKey_Space);
    cleanKey = configJson.value("cleanKey", ImGuiKey_V);
    prevSkinKey = configJson.value("prevSkinKey", ImGuiKey_PageUp);
    nextSkinKey = configJson.value("nextSkinKey", ImGuiKey_PageDown);
    menuKey = configJson.value("menuKey", ImGuiKey_Insert);
    targeting = configJson.value("targeting", 0);
    in.close();
  }

  void Save() {
    const auto self = script::self;
    auto out = std::ofstream("setting");
    if(!out.good()) {
      return;
    }
    if(self) {
      configJson[std::string(self->dataStack()->baseSkin.model.str) + ".currentSkinIndex"] = currentSkin;
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
}// namespace config