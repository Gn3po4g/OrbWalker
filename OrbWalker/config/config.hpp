#pragma once

namespace config {
constexpr enum class Targeting : int {
  health_lowest,
  distance_closest,
};
constexpr const char* targetingStr[] = {
  "health-lowest",
  "distance-closest",
};

inline bool showMenu {true};

inline bool showAttackRange {true};
inline Targeting targeting {};
inline ImGuiKey kiteKey {ImGuiKey_Space};
inline ImGuiKey cleanKey {ImGuiKey_V};

inline int currentSkin {};
inline ImGuiKey prevSkinKey {ImGuiKey_PageUp};
inline ImGuiKey nextSkinKey {ImGuiKey_PageDown};

inline ImGuiKey menuKey {ImGuiKey_Insert};

void Load();
void Save();
}  // namespace config
