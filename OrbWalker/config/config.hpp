namespace config {
  extern bool showMenu;

  extern ImGuiKey kiteKey;
  extern ImGuiKey cleanKey;

  extern ImGuiKey prevSkinKey;
  extern ImGuiKey nextSkinKey;

  extern ImGuiKey menuKey;

  enum class Targeting : int {
    health_lowest,
    distance_closest
  };
  constexpr auto TargetingStr = std::to_array(
      {"health-lowest",
       "distance-closest"});
  //inline const char *TargetingStr[] = {"health-lowest", "distance-closest"};
  extern int targeting;
}// namespace config
