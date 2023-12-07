#pragma once

class skin {
public:
  static skin &inst();

  struct SkinInfo {
    std::string modelName;
    std::string skinName;
    i32 skinId;
  };

  struct SpecialSkin {
    std::string champName;
    i32 skinIdStart;
    i32 skinIdEnd;
    std::vector<std::string> gears;
  };

  std::vector<SkinInfo> championSkins;

  std::vector<SpecialSkin> specialSkins{
    {"Katarina",    29, 36, {"Dagger 1", "Dagger 2", "Dagger 3", "Dagger 4", "Dagger 5", "Dagger 6"}},
    {"Renekton",    26, 32, {"Head off", "Head on", "Fins", "Ultimate"}                             },
    {"MissFortune", 16, 16, {"Scarlet fair", "Zero hour", "Royal arms", "Starswarm"}                },
    {"Ezreal",      5,  5,  {"Level 1", "Level 2", "Level 3"}                                       }
  };

  void update();
  void ChangeSkin(std::string_view, i32);
  std::vector<std::string> skins_name();
  i64 special_skin();

private:
  skin();
  inline static std::unique_ptr<skin> instance_;
};