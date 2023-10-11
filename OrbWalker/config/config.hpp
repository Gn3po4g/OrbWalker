#pragma once

namespace config {
enum Selector : int {
  health_lowest,
  distance_closest,
  count
};

inline bool showMenu{true};

inline bool showAttackRange{true};
inline int selector{};
inline ImGuiKey kiteKey{ImGuiKey_Space};
inline ImGuiKey cleanKey{ImGuiKey_V};

inline int currentSkin{};
inline ImGuiKey prevSkinKey{ImGuiKey_PageUp};
inline ImGuiKey nextSkinKey{ImGuiKey_PageDown};

inline ImGuiKey menuKey{ImGuiKey_Insert};

void Load();
void Save();
} // namespace config
