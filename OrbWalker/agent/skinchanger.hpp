#pragma once

class skin {
public:
  static skin &inst();

  struct SkinInfo {
    std::string modelName;
    std::string skinName;
    int32_t skinId;
  };

  struct SpecialSkin {
    uint64_t champName;
    int32_t skinIdStart;
    int32_t skinIdEnd;
    std::vector<std::string> gears;
  };

  std::vector<SkinInfo> championsSkins;

  std::vector<SpecialSkin> specialSkins{
    {"Katarina"_FNV,    29, 36, {"Dagger 1", "Dagger 2", "Dagger 3", "Dagger 4", "Dagger 5", "Dagger 6"}},
    {"Renekton"_FNV,    26, 32, {"Head off", "Head on", "Fins", "Ultimate"}                             },
    {"MissFortune"_FNV, 16, 16, {"Scarlet fair", "Zero hour", "Royal arms", "Starswarm"}                },
    {"Ezreal"_FNV,      5,  5,  {"Level 1", "Level 2", "Level 3"}                                       }
  };

  void update();
  void ChangeSkin(std::string_view, int32_t);

private:
  skin();
  inline static std::unique_ptr<skin> instance_;
};