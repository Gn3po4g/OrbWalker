namespace config {
  extern bool showMenu;

  extern bool showAttackRange;
  extern int targeting;
  extern ImGuiKey kiteKey;
  extern ImGuiKey cleanKey;

  extern int currentSkin;
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


  void Load();
  void Save();
}// namespace config
