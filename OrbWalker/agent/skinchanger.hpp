namespace skin {
  class SkinInfo {
  public:
    const char *modelName;
    std::string skinName;
    std::int32_t skinId;
  };

  class SpecialSkin {
  public:
    uint64_t champHash;
    int32_t skinIdStart;
    int32_t skinIdEnd;
    std::vector<const char *> gears;
  };

  extern std::map<uint64_t, std::vector<SkinInfo>> championsSkins;

  inline auto specialSkins = std::to_array<SpecialSkin>(
      {{FNV("Katarina"), 29, 36, {"Dagger 1", "Dagger 2", "Dagger 3", "Dagger 4", "Dagger 5", "Dagger 6"}},
       {FNV("Renekton"), 26, 32, {"Head off", "Head on", "Fins", "Ultimate"}},
       {FNV("MissFortune"), 16, 16, {"Scarlet fair", "Zero hour", "Royal arms", "Starswarm"}},
       {FNV("Ezreal"), 5, 5, {"Level 1", "Level 2", "Level 3"}}});

  void Load();

  void Update();
}// namespace skin