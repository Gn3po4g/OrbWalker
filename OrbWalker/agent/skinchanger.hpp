namespace skin {
  class SkinInfo {
  public:
    const char *model_name;
    std::string skin_name;
    std::int32_t skin_id;
  };

  class SpecialSkin {
  public:
    uint64_t champHash;
    int32_t skinIdStart;
    int32_t skinIdEnd;
    std::vector<const char *> gears;
  };

  extern std::map<uint64_t, std::vector<SkinInfo>> champions_skins;

  extern std::vector<SpecialSkin> specialSkins;

  void Load();

  void Update();
}// namespace skin