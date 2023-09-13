#include "stdafx.hpp"

namespace skin {
  std::map<std::uint64_t, std::vector<SkinInfo>> champions_skins;

  std::vector<SpecialSkin> specialSkins{
      {FNV("Katarina"), 29, 36, {"Dagger 1", "Dagger 2", "Dagger 3", "Dagger 4", "Dagger 5", "Dagger 6"}},
      {FNV("Renekton"), 26, 32, {"Head off", "Head on", "Fins", "Ultimate"}},
      {FNV("MissFortune"), 16, 16, {"Scarlet fair", "Zero hour", "Royal arms", "Starswarm"}},
      {FNV("Ezreal"), 5, 5, {"Level 1", "Level 2", "Level 3"}}};

  void Load() {
    auto addr = (uintptr_t)GetModuleHandle(nullptr) + 0x218C350;
    const auto &champions = *(std::vector<Champion *> *)(*(uintptr_t *)(addr) + 0x18);
    for(const auto &champion : champions) {
      std::vector<std::int32_t> skins_ids;
      for(auto &sk : champion->skins())
        skins_ids.push_back(sk.skin_id);

      std::ranges::sort(skins_ids);

      std::map<std::string, std::int32_t> temp_skin_list;
      for(const auto &i : skins_ids) {
        const auto name = champion->champion_name();
        const auto skin_display_name{std::string("game_character_skin_displayname_") + name.str + "_" + std::to_string(i)};
        using translateString_t = const char *(__fastcall *)(const char *);
        translateString_t translateString = translateString_t((uintptr_t)GetModuleHandle(nullptr) + 0xCF0F80);
        auto skin_display_name_translated{i > 0 ? std::string(translateString(skin_display_name.c_str())) : std::string(name.str, name.length)};

        if(skin_display_name_translated == skin_display_name) {
          continue;
        }

        if(const auto it{temp_skin_list.find(skin_display_name_translated)}; it == temp_skin_list.end()) {
          temp_skin_list[skin_display_name_translated] = 1;
        } else {
          skin_display_name_translated.append(" Chroma " + std::to_string(it->second));
          it->second = it->second + 1;
        }

        const auto champ_name{fnv::hash_runtime(champion->champion_name().str)};
        champions_skins[champ_name].push_back({champion->champion_name().str, skin_display_name_translated, i});

        if(i == 7 && champ_name == FNV("Lux")) {
          champions_skins[champ_name].push_back({"LuxAir", "Elementalist Air Lux", i});
          champions_skins[champ_name].push_back({"LuxDark", "Elementalist Dark Lux", i});
          champions_skins[champ_name].push_back({"LuxFire", "Elementalist Fire Lux", i});
          champions_skins[champ_name].push_back({"LuxIce", "Elementalist Ice Lux", i});
          champions_skins[champ_name].push_back({"LuxMagma", "Elementalist Magma Lux", i});
          champions_skins[champ_name].push_back({"LuxMystic", "Elementalist Mystic Lux", i});
          champions_skins[champ_name].push_back({"LuxNature", "Elementalist Nature Lux", i});
          champions_skins[champ_name].push_back({"LuxStorm", "Elementalist Storm Lux", i});
          champions_skins[champ_name].push_back({"LuxWater", "Elementalist Water Lux", i});
        } else if(i == 6 && champ_name == FNV("Sona")) {
          champions_skins[champ_name].push_back({"SonaDJGenre02", "DJ Sona 2", i});
          champions_skins[champ_name].push_back({"SonaDJGenre03", "DJ Sona 3", i});
        }
      }
    }
    if(config::currentSkin > 0) {
      const auto &values{champions_skins[fnv::hash_runtime(script::self->characterDataStack()->baseSkin.model.str)]};
      script::self->ChangeSkin(values[config::currentSkin - 1].model_name, values[config::currentSkin - 1].skin_id);
    }
  }

  void Update() {
    if(ImGui::IsKeyPressed(config::prevSkinKey)) {
      if(const auto self = script::self; self) {
        const auto &values{champions_skins[fnv::hash_runtime(self->characterDataStack()->baseSkin.model.str)]};
        if(--config::currentSkin > 0) {
          self->ChangeSkin(values[config::currentSkin - 1].model_name, values[config::currentSkin - 1].skin_id);
        } else {
          config::currentSkin = 1;
          config::Save();
        }
      }
    } else if(ImGui::IsKeyPressed(config::nextSkinKey)) {
      if(const auto self = script::self; self) {
        const auto &values{champions_skins[fnv::hash_runtime(self->characterDataStack()->baseSkin.model.str)]};
        if(++config::currentSkin > (int32_t)values.size()) {
          config::currentSkin = (int32_t)values.size();
        }
        if(config::currentSkin > 0) {
          self->ChangeSkin(values[config::currentSkin - 1].model_name, values[config::currentSkin - 1].skin_id);
        }
        config::Save();
      }
    }
  }
}// namespace skin