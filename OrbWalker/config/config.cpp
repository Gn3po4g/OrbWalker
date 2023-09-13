#include "stdafx.hpp"

namespace config {
  bool showMenu{true};

  ImGuiKey kiteKey{ImGuiKey_Space};
  ImGuiKey cleanKey{ImGuiKey_V};

  ImGuiKey prevSkinKey{ImGuiKey_PageUp};
  ImGuiKey nextSkinKey{ImGuiKey_PageDown};

  ImGuiKey menuKey{ImGuiKey_Insert};

  int targeting{};
}// namespace config