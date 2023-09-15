#include "stdafx.hpp"

namespace skin {
using namespace std;

map<uint64_t, vector<SkinInfo>> championsSkins;

void ChangeModelForObject(Object* obj, const char* model, int32_t skin) {
  if(skin == -1) {
    return;
  }

  if(const auto stack = obj->dataStack(); stack->baseSkin.skin != skin) {
    stack->baseSkin.skin = skin;
    stack->stack.clear();
    stack->push(model, skin);
  }
}

void ChangeSkinForObject(Object* obj, int32_t skin) noexcept {
  if(skin == -1) {
    return;
  }
  if(const auto stack = obj->dataStack(); stack->baseSkin.skin != skin) {
    stack->baseSkin.skin = skin;
    stack->update(true);
  }
}

void Load() {
  const auto& champions = *(vector<Champion*>*)(*(uintptr_t*)(offset::oChampionManager) + 0x18);
  for(const auto& champion : champions) {
    vector<int32_t> skinsIds;
    for(auto& sk : champion->skins()) { skinsIds.push_back(sk.skinId); }
    ranges::sort(skinsIds);
    map<string, int32_t> tempSkinList;
    for(const auto& i : skinsIds) {
      const auto name = champion->champion_name();
      const auto skinDisplayname = format("game_character_skin_displayname_{}_{}", name.str, i);
      using fnTranslateString = const char*(__fastcall*)(const char*);
      fnTranslateString TranslateString = fnTranslateString(offset::oTranslateString);
      auto translatedName = i > 0 ? string(TranslateString(skinDisplayname.data())) : string(name.str, name.length);
      if(translatedName == skinDisplayname) {
        continue;
      }
      if(const auto it {tempSkinList.find(translatedName)}; it == tempSkinList.end()) {
        tempSkinList[translatedName] = 1;
      } else {
        translatedName.append(" Chroma " + to_string(it->second));
        ++it->second;
      }
      const auto champName = FNV(champion->champion_name().str);
      championsSkins[champName].emplace_back(champion->champion_name().str, translatedName, i);
      if(i == 7 && champName == FNV("Lux")) {
        championsSkins[champName].emplace_back("LuxAir", "Elementalist Air Lux", i);
        championsSkins[champName].emplace_back("LuxDark", "Elementalist Dark Lux", i);
        championsSkins[champName].emplace_back("LuxFire", "Elementalist Fire Lux", i);
        championsSkins[champName].emplace_back("LuxIce", "Elementalist Ice Lux", i);
        championsSkins[champName].emplace_back("LuxMagma", "Elementalist Magma Lux", i);
        championsSkins[champName].emplace_back("LuxMystic", "Elementalist Mystic Lux", i);
        championsSkins[champName].emplace_back("LuxNature", "Elementalist Nature Lux", i);
        championsSkins[champName].emplace_back("LuxStorm", "Elementalist Storm Lux", i);
        championsSkins[champName].emplace_back("LuxWater", "Elementalist Water Lux", i);
      } else if(i == 6 && champName == FNV("Sona")) {
        championsSkins[champName].emplace_back("SonaDJGenre02", "DJ Sona 2", i);
        championsSkins[champName].emplace_back("SonaDJGenre03", "DJ Sona 3", i);
      }
    }
  }
  if(config::currentSkin > 0) {
    const auto& values {championsSkins[FNV(script::self->dataStack()->baseSkin.model.str)]};
    script::self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
  }
}

void Update() {
  const auto self = script::self;
  if(!self) {
    return;
  }
  if(ImGui::IsKeyPressed(ImGuiKey_5)) {
    if(!ImGui::GetIO().KeysDown[ImGuiKey_LeftCtrl]) {
      return;
    }
    const auto playerHash = FNV(self->dataStack()->baseSkin.model.str);
    if(const auto it = ranges::find_if(
         specialSkins, [&skin = self->dataStack()->baseSkin.skin, &ph = playerHash](const SpecialSkin& x
                       ) { return x.champHash == ph && (x.skinIdStart <= skin && x.skinIdEnd >= skin); }
       );
       it != specialSkins.end()) {
      const auto stack = self->dataStack();
      if(stack->baseSkin.gear < (int8_t)it->gears.size() - 1) {
        ++stack->baseSkin.gear;
      } else {
        stack->baseSkin.gear = 0;
      }
      stack->update(true);
    }
  }
  if(ImGui::IsKeyPressed(config::prevSkinKey)) {
    const auto& values {championsSkins[FNV(self->dataStack()->baseSkin.model.str)]};
    if(--config::currentSkin > 0) {
      self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
    } else {
      config::currentSkin = 1;
      config::Save();
    }

  } else if(ImGui::IsKeyPressed(config::nextSkinKey)) {
    const auto& values {championsSkins[FNV(self->dataStack()->baseSkin.model.str)]};
    if(++config::currentSkin > (int32_t)values.size()) {
      config::currentSkin = (int32_t)values.size();
    }
    if(config::currentSkin > 0) {
      self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
    }
    config::Save();
  }
  if(!self->dataStack()->stack.empty()) {
    if(auto& stack = self->dataStack()->stack.front(); stack.skin != self->dataStack()->baseSkin.skin) {
      stack.skin = self->dataStack()->baseSkin.skin;
      self->dataStack()->update(true);
    }
  }
  for(auto minion : script::minions->data()) {
    const auto hash = FNV(minion->dataStack()->baseSkin.model.str);
    const auto playerHash = FNV(self->dataStack()->baseSkin.model.str);
    if(const auto owner = minion->GetOwner(); owner) {
      if(hash == FNV("TestCubeRender10Vision")) {
        if(owner == self) {
          if(playerHash == FNV("Yone")) {
            ChangeModelForObject(minion, "Yone", self->dataStack()->baseSkin.skin);
          } else {
            ChangeSkinForObject(minion, 0);
          }
        }
      } else if(hash != FNV("SRU_Jungle_Companions") && hash != FNV("DominationScout")) {
        ChangeSkinForObject(minion, owner->dataStack()->baseSkin.skin);
      }
      continue;
    }
    if((hash == FNV("NunuSnowball") && playerHash == FNV("Nunu")) || (hash == FNV("KindredWolf") && playerHash == FNV("Kindred")) || (hash == FNV("QuinnValor") && playerHash == FNV("Quinn"))) {
      ChangeSkinForObject(minion, self->dataStack()->baseSkin.skin);
    }
  }
}
}  // namespace skin