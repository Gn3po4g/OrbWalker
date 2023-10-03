#include "pch.hpp"

#include "agent/orb.hpp"
#include "class/struct.hpp"
#include "config/config.hpp"
#include "memory/offset.hpp"
#include "skinchanger.hpp"

#include "agent/orb.hpp"
#include "class/struct.hpp"
#include "config/config.hpp"
#include "memory/offset.hpp"
#include "skinchanger.hpp"

namespace skin {
using namespace std;

map<uint64_t, vector<SkinInfo>> championsSkins;

void ChangeModelForObject(Object *obj, const char *model, int32_t skin) {
  if(skin == -1) { return; }

  if(const auto stack = obj->dataStack(); stack->baseSkin.skin != skin) {
    stack->baseSkin.skin = skin;
    stack->stack.clear();
    stack->push(model, skin);
  }
}

void ChangeSkinForObject(Object *obj, int32_t skin) noexcept {
  if(skin == -1) { return; }
  if(const auto stack = obj->dataStack(); stack->baseSkin.skin != skin) {
    stack->baseSkin.skin = skin;
    stack->update(true);
  }
}

void Load() {
  const auto &champions = *(vector<Champion *> *)(*(uintptr_t *)(offset->oChampionManager) + 0x18);
  for(const auto &champion : champions) {
    vector<int32_t> skinsIds;
    for(auto &sk : std::span(champion->skins().data, champion->skins().size)) { skinsIds.push_back(sk.skinId); }
    ranges::sort(skinsIds);
    map<string, int32_t> tempSkinList;
    for(const auto &i : skinsIds) {
      const auto name = champion->championName();
      const auto skinDisplayname = format("game_character_skin_displayname_{}_{}", name.str, i);
      using fnTranslateString = const char *(__fastcall *)(const char *);
      fnTranslateString TranslateString = fnTranslateString(offset->oTranslateString);
      string translatedName = i > 0 ? TranslateString(skinDisplayname.data()) : name.str;
      if(translatedName == skinDisplayname) { continue; }
      if(const auto it{tempSkinList.find(translatedName)}; it == tempSkinList.end()) {
        tempSkinList[translatedName] = 1;
      } else {
        translatedName.append(" Chroma " + to_string(it->second++));
      }
      const auto champName = FNV(champion->championName());
      championsSkins[champName].emplace_back(champion->championName(), translatedName, i);
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
}

void Update() {
  const auto self = orb->self;
  if(!self) { return; }
  static std::once_flag changeSkin;
  std::call_once(changeSkin, [self]() {
    if(config::currentSkin > 0) {
      const auto &values{championsSkins[FNV(self->dataStack()->baseSkin.model)]};
      self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
    }
  });
  if(ImGui::IsKeyPressed(ImGuiKey_5)) {
    if(!ImGui::GetIO().KeysDown[ImGuiKey_LeftCtrl]) { return; }
    const auto playerHash = FNV(self->dataStack()->baseSkin.model);
    if(const auto it = ranges::find_if(
         specialSkins,
         [&](const SpecialSkin &x) {
           auto skin = self->dataStack()->baseSkin.skin;
           return x.champHash == playerHash && (x.skinIdStart <= skin && x.skinIdEnd >= skin);
         }
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
    const auto &values{championsSkins[FNV(self->dataStack()->baseSkin.model)]};
    if(--config::currentSkin > 0) {
      self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
    } else {
      config::currentSkin = 1;
      config::Save();
    }
  } else if(ImGui::IsKeyPressed(config::nextSkinKey)) {
    const auto &values{championsSkins[FNV(self->dataStack()->baseSkin.model)]};
    if(++config::currentSkin > (int32_t)values.size()) { config::currentSkin = (int32_t)values.size(); }
    if(config::currentSkin > 0) {
      self->ChangeSkin(values[config::currentSkin - 1].modelName, values[config::currentSkin - 1].skinId);
    }
    config::Save();
  }
  if(!self->dataStack()->stack.empty()) {
    if(const auto championName{FNV(self->dataStack()->baseSkin.model)};
       championName != FNV("Viego") && championName != FNV("Sylas")) {
      if(auto &stack = self->dataStack()->stack.front(); stack.skin != self->dataStack()->baseSkin.skin) {
        stack.skin = self->dataStack()->baseSkin.skin;
        self->dataStack()->update(true);
      }
    }
  }
  for(auto minion : span(orb->minions->data, orb->minions->size)) {
    const auto hash = FNV(minion->dataStack()->baseSkin.model);
    const auto playerHash = FNV(self->dataStack()->baseSkin.model);
    if(const auto owner = minion->GetOwner(); owner) {
      if(hash == FNV("TestCubeRender10Vision")) {
        if(owner == self) {
          if(playerHash == FNV("Yone")) {
            ChangeModelForObject(minion, "Yone", self->dataStack()->baseSkin.skin);
          } else {
            ChangeSkinForObject(minion, 0);
          }
        }
      } else if(hash != FNV("SRU_Jungle_Companions") && hash != FNV("DominationScout") && hash != FNV("JammerDevice") && hash != FNV("SightWard") && hash != FNV("YellowTrinket") && hash != FNV("VisionWard") && hash != FNV("BlueTrinket")) {
        ChangeSkinForObject(minion, owner->dataStack()->baseSkin.skin);
      }
      continue;
    }
    if((hash == FNV("NunuSnowball") && playerHash == FNV("Nunu")) || (hash == FNV("KindredWolf") && playerHash == FNV("Kindred")) || (hash == FNV("QuinnValor") && playerHash == FNV("Quinn"))) {
      ChangeSkinForObject(minion, self->dataStack()->baseSkin.skin);
    }
  }
}
} // namespace skin