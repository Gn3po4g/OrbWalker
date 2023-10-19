#include "pch.hpp"

#include "skinchanger.hpp"

#include "class/champion.hpp"
#include "config/config.hpp"
#include "memory/global.hpp"
#include "memory/offset.hpp"

#include "memory/function.hpp"

using namespace std;

bool skin_valid(Object *obj) {
  switch(FNV(obj->dataStack()->baseSkin.model)) {
  case FNVC("DominationScout"):
  case FNVC("JammerDevice"):
  case FNVC("SightWard"):
  case FNVC("YellowTrinket"):
  case FNVC("VisionWard"):
  case FNVC("BlueTrinket"):
  case FNVC("SRU_Jungle_Companions"):
    return false;
  default:
    return true;
  }
}

bool is_companion(uint64_t owner, uint64_t obj) {
  switch(owner) {
  case FNVC("Kindred"):
    return obj == FNVC("KindredWolf");
  case FNVC("Nunu"):
    return obj == FNVC("NunuSnowball");
  case FNVC("Quinn"):
    return obj == FNVC("QuinnValor");
  default:
    return false;
  }
}

void ChangeModelForObject(Object *obj, const char *model, int32_t skin) {
  if(skin == -1) { return; }
  if(const auto stack = obj->dataStack(); stack->baseSkin.skin_id != skin) {
    stack->baseSkin.skin_id = skin;
    stack->stack.clear();
    stack->push(model, skin);
  }
}

void ChangeSkinForObject(Object *obj, int32_t skin) noexcept {
  if(skin == -1) { return; }
  if(const auto stack = obj->dataStack(); stack->baseSkin.skin_id != skin) {
    stack->baseSkin.skin_id = skin;
    stack->update(true);
  }
}

void skin::ChangeSkin(std::string_view model, int32_t skin_id) {
  static auto CheckSpecialSkins = [&, stack{self->dataStack()}](std::string_view model, int32_t skin_id) {
    const auto champName{FNV(stack->baseSkin.model)};
    if(std::ranges::count_if(specialSkins, [&](const SpecialSkin &special_skin) {
         return special_skin.champHash == champName && skin_id >= special_skin.skinIdStart
             && skin_id <= special_skin.skinIdEnd;
       })) {
      // stack->stack.clear();
      stack->baseSkin.gear = 0;
      stack->update(true);
    } else if(champName == FNVC("Lux") && skin_id == 7 || champName == FNVC("Sona") && skin_id == 6) {
      stack->stack.clear();
      stack->push(model.data(), skin_id);
    } else if(champName != FNVC("Kayn")) {
      stack->baseSkin.gear = static_cast<int8_t>(-1);
      stack->update(true);
    }
  };
  const auto stack{self->dataStack()};
  ((xor_value<int32_t> *)((uintptr_t)self.get() + objSkinId))->encrypt(skin_id);
  stack->baseSkin.skin_id = skin_id;
  CheckSpecialSkins(model, skin_id);
}

skin &skin::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] {
    instance_.reset(new skin());
  });
  return *instance_;
}

skin::skin() {
  const auto &default_skin = self->dataStack()->baseSkin;
  championsSkins.emplace_back(default_skin.model.get(), "Default", default_skin.skin_id);
  const auto champions = Read<vector<Champion *>>(Read<uintptr_t>(oChampionManager) + 0x18);
  if(const auto it{ranges::find_if(
       champions,
       [](Champion *champion) {
         return self->name() == champion->championName().get();
       }
     )};
     it != champions.end()) {
    const auto champion = *it;
    auto skins_id = champion->skins_id();
    // ranges::sort(skins_id);
    map<string, int32_t> tempSkinList;
    for(auto &i : skins_id) {
      auto name = champion->championName();
      using fnTranslateString = const char *(__fastcall *)(const char *);
      string translatedName =
        i > 0
          ? ((fnTranslateString)oTranslateString)(format("game_character_skin_displayname_{}_{}", name.get(), i).data())
          : name;
      if(auto it{tempSkinList.find(translatedName)}; it == tempSkinList.end()) {
        tempSkinList[translatedName] = 1;
      } else {
        translatedName.append(" Chroma " + to_string(it->second++));
      }
      championsSkins.emplace_back(champion->championName().get(), translatedName, i);
      const auto champName = FNV(champion->championName());
      if(i == 7 && champName == FNVC("Lux")) {
        championsSkins.emplace_back("LuxAir", "Elementalist Air Lux", i);
        championsSkins.emplace_back("LuxDark", "Elementalist Dark Lux", i);
        championsSkins.emplace_back("LuxFire", "Elementalist Fire Lux", i);
        championsSkins.emplace_back("LuxIce", "Elementalist Ice Lux", i);
        championsSkins.emplace_back("LuxMagma", "Elementalist Magma Lux", i);
        championsSkins.emplace_back("LuxMystic", "Elementalist Mystic Lux", i);
        championsSkins.emplace_back("LuxNature", "Elementalist Nature Lux", i);
        championsSkins.emplace_back("LuxStorm", "Elementalist Storm Lux", i);
        championsSkins.emplace_back("LuxWater", "Elementalist Water Lux", i);
      } else if(i == 6 && champName == FNVC("Sona")) {
        championsSkins.emplace_back("SonaDJGenre02", "DJ Sona 2", i);
        championsSkins.emplace_back("SonaDJGenre03", "DJ Sona 3", i);
      }
    }
  }
}

void skin::update() {
  if(!self) { return; }
  auto &config = config::inst();
  static std::once_flag init_skin;
  std::call_once(init_skin, [&] {
    if(config.current_skin > 0) {
      const auto &[modelName, skinName, skinId]{championsSkins[config.current_skin]};
      ChangeSkin(modelName, skinId);
    }
  });
  if(ImGui::IsKeyPressed(ImGuiKey_5)) {
    if(!ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) { return; }
    const auto player_hash = FNV(self->dataStack()->baseSkin.model);
    if(const auto it = ranges::find_if(
         specialSkins,
         [&](const SpecialSkin &x) {
           const auto skin = self->dataStack()->baseSkin.skin_id;
           return x.champHash == player_hash && (x.skinIdStart <= skin && x.skinIdEnd >= skin);
         }
       );
       it != specialSkins.end()) {
      const auto stack = self->dataStack();
      stack->baseSkin.gear = (stack->baseSkin.gear + 1) % it->gears.size();
      stack->update(true);
    }
  }
  if(ImGui::IsKeyPressed(config.prev_skin_key)) {
    config.current_skin = std::max(config.current_skin - 1, 0);
    const auto &[modelName, skinName, skinId] = championsSkins[config.current_skin];
    ChangeSkin(modelName, skinId);

    config.save();
  } else if(ImGui::IsKeyPressed(config.next_skin_key)) {
    config.current_skin = std::min(config.current_skin + 1, static_cast<int>(championsSkins.size() - 1));
    const auto &[modelName, skinName, skinId] = championsSkins[config.current_skin];
    ChangeSkin(modelName, skinId);
    config.save();
  }
  if(!self->dataStack()->stack.empty()) {
    if(const auto player_hash{FNV(self->dataStack()->baseSkin.model)};
       player_hash != FNVC("Viego") && player_hash != FNVC("Sylas")) {
      if(auto &[model, _1, skin_id, _2, gear, _3] = self->dataStack()->stack.front();
         skin_id != self->dataStack()->baseSkin.skin_id) {
        skin_id = self->dataStack()->baseSkin.skin_id;
        self->dataStack()->update(true);
      }
    }
  }
  for(const auto minion : span(minions->data, minions->size)) {
    const auto hash = FNV(minion->dataStack()->baseSkin.model);
    const auto player_hash = FNV(self->dataStack()->baseSkin.model);
    if(const auto owner = minion->GetOwner(); owner == self.get()) {
      if(hash == FNVC("TestCubeRender10Vision")) {
        if(player_hash == FNVC("Yone")) ChangeModelForObject(minion, "Yone", self->dataStack()->baseSkin.skin_id);
        else ChangeSkinForObject(minion, 0);
      } else if(skin_valid(minion)) {
        ChangeSkinForObject(minion, owner->dataStack()->baseSkin.skin_id);
      }
      continue;
    }
    if(is_companion(player_hash, hash)) { ChangeSkinForObject(minion, self->dataStack()->baseSkin.skin_id); }
  }
}
