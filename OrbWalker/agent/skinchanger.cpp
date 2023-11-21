#include "pch.hpp"

#include "skinchanger.hpp"

#include "class/champion.hpp"
#include "config/config.hpp"
#include "memory/offset.hpp"

#include "memory/function.hpp"
#include <class/obj_list.hpp>

using namespace std;

bool skin_valid(hash_type obj) {
  switch (obj) {
  case "JammerDevice"_FNV:
  case "SightWard"_FNV:
  case "YellowTrinket"_FNV:
  case "VisionWard"_FNV:
  case "BlueTrinket"_FNV:
  case "DominationScout"_FNV:
  case "SRU_Jungle_Companions"_FNV:
  case "SRU_RiftHerald_Mercenary"_FNV:
  case "TestCubeRender10Vision"_FNV:
  case "ViegoSoul"_FNV:
    return false;
  default:
    return true;
  }
}

bool is_companion(hash_type owner, hash_type obj) {
  switch (owner) {
  case "Kindred"_FNV:
    return obj == "KindredWolf"_FNV;
  case "Nunu"_FNV:
    return obj == "NunuSnowball"_FNV;
  case "Quinn"_FNV:
    return obj == "QuinnValor"_FNV;
  default:
    return false;
  }
}

void ChangeModelForObject(Object *obj, const char *model, int32_t skin) {
  if (skin == -1) { return; }
  if (const auto stack = obj->dataStack(); stack->baseSkin.skin_id != skin) {
    stack->baseSkin.skin_id = skin;
    stack->stack.clear();
    stack->push(model, skin);
  }
}

void ChangeSkinForObject(Object *obj, i32 skin) noexcept {
  if (skin == -1) { return; }
  if (const auto stack = obj->dataStack(); stack->baseSkin.skin_id != skin) {
    stack->baseSkin.skin_id = skin;
    stack->stack.clear();
    stack->push(stack->baseSkin.model.str(), skin);
    // stack->update(false);
  }
}

void skin::ChangeSkin(std::string_view model, i32 skin_id) {
  static auto CheckSpecialSkins = [&](string_view model, int32_t skin_id) {
    const auto stack{Object::self()->dataStack()};
    const auto champName{FNV(stack->baseSkin.model.str())};
    if (std::ranges::count_if(specialSkins, [&](const SpecialSkin &special_skin) {
          return special_skin.champName == champName && skin_id >= special_skin.skinIdStart
              && skin_id <= special_skin.skinIdEnd;
        })) {
      // stack->stack.clear();
      stack->baseSkin.gear = 0;
      stack->update(true);
    } else if (champName == "Lux"_FNV && skin_id == 7 || champName == "Sona"_FNV && skin_id == 6) {
      stack->stack.clear();
      stack->push(model.data(), skin_id);
    } else if (champName != "Kayn"_FNV) {
      stack->baseSkin.gear = static_cast<int8_t>(-1);
      stack->update(true);
    }
  };
  const auto stack{Object::self()->dataStack()};
  ((xor_value<i32> *)((uptr)Object::self() + objSkinId))->encrypt(skin_id);
  stack->baseSkin.skin_id = skin_id;
  CheckSpecialSkins(model, skin_id);
}

skin &skin::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(new skin()); });
  return *instance_;
}

skin::skin() {
  const auto &default_skin = Object::self()->dataStack()->baseSkin;
  championsSkins.emplace_back(default_skin.model.str(), "Default", default_skin.skin_id);
  const auto champions = Read<vector<Champion *>>(Read<uintptr_t>(RVA(oChampionManager)) + 0x18);
  if (const auto it{ranges::find_if(
        champions, [](Champion *champion) { return Object::self()->name() == champion->championName().str(); }
      )};
      it != champions.end()) {
    const auto champion = *it;
    auto skins_id       = champion->skins_id();
    map<hash_type, i32> tempSkinList;
    for (auto &i : skins_id) {
      const auto name           = champion->championName().str();
      const auto skin_fmt       = "game_character_skin_displayname_{}_{}";
      const auto name_fmt       = "game_character_displayname_{}";
      const auto formatted_name = i ? format(skin_fmt, name, i) : format(name_fmt, name);
      auto translatedName       = string(call_function<const char *>(RVA(oTranslateString), formatted_name.data()));
      if (tempSkinList.count(FNV(translatedName))) {
        translatedName.append(" Chroma " + to_string(tempSkinList[FNV(translatedName)]++));
      } else {
        tempSkinList[FNV(translatedName)] = 1;
      }
      championsSkins.emplace_back(name, translatedName, i);
      const auto name_hash = FNV(name);
      if (i == 7 && name_hash == "Lux"_FNV) {
        championsSkins.emplace_back("LuxAir", "Elementalist Air Lux", i);
        championsSkins.emplace_back("LuxDark", "Elementalist Dark Lux", i);
        championsSkins.emplace_back("LuxFire", "Elementalist Fire Lux", i);
        championsSkins.emplace_back("LuxIce", "Elementalist Ice Lux", i);
        championsSkins.emplace_back("LuxMagma", "Elementalist Magma Lux", i);
        championsSkins.emplace_back("LuxMystic", "Elementalist Mystic Lux", i);
        championsSkins.emplace_back("LuxNature", "Elementalist Nature Lux", i);
        championsSkins.emplace_back("LuxStorm", "Elementalist Storm Lux", i);
        championsSkins.emplace_back("LuxWater", "Elementalist Water Lux", i);
      } else if (i == 6 && name_hash == "Sona"_FNV) {
        championsSkins.emplace_back("SonaDJGenre02", "DJ Sona 2", i);
        championsSkins.emplace_back("SonaDJGenre03", "DJ Sona 3", i);
      }
    }
  }
}

void skin::update() {
  auto &config = config::inst();
  static std::once_flag init_skin;
  std::call_once(init_skin, [&] {
    if (config.current_skin > 0) {
      auto index = std::min((size_t)config.current_skin, championsSkins.size());
      const auto &[modelName, skinName, skinId]{championsSkins[index]};
      ChangeSkin(modelName, skinId);
    }
  });
  const auto player_hash = FNV(Object::self()->dataStack()->baseSkin.model.str());
  if (ImGui::IsKeyPressed(ImGuiKey_5) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
    if (const auto it = ranges::find_if(
          specialSkins,
          [&](const SpecialSkin &x) {
            const auto skin = Object::self()->dataStack()->baseSkin.skin_id;
            return x.champName == player_hash && (x.skinIdStart <= skin && x.skinIdEnd >= skin);
          }
        );
        it != specialSkins.end()) {
      const auto stack     = Object::self()->dataStack();
      stack->baseSkin.gear = (stack->baseSkin.gear + 1) % it->gears.size();
      stack->update(true);
    }
  }
  if (ImGui::IsKeyPressed(config.prev_skin_key)) {
    config.current_skin                       = std::max(config.current_skin - 1, 0);
    const auto &[modelName, skinName, skinId] = championsSkins[config.current_skin];
    ChangeSkin(modelName, skinId);
    config.save();
  } else if (ImGui::IsKeyPressed(config.next_skin_key)) {
    config.current_skin = std::min(config.current_skin + 1, static_cast<int>(championsSkins.size() - 1));
    const auto &[modelName, skinName, skinId] = championsSkins[config.current_skin];
    ChangeSkin(modelName, skinId);
    config.save();
  }
  if (!Object::self()->dataStack()->stack.empty()) {
    if (player_hash != "Viego"_FNV && player_hash != "Sylas"_FNV) {
      if (auto &[model, _1, skin_id, _2, gear, _3] = Object::self()->dataStack()->stack.front();
          skin_id != Object::self()->dataStack()->baseSkin.skin_id) {
        skin_id = Object::self()->dataStack()->baseSkin.skin_id;
        Object::self()->dataStack()->update(true);
      }
    }
  }
  for (const auto minion : span(ObjList::minions()->data, ObjList::minions()->size)) {
    const auto hash{FNV(minion->dataStack()->baseSkin.model.str())};
    if (const auto owner{minion->GetOwner()}; owner == Object::self()) {
      if (hash == "TestCubeRender10Vision"_FNV && player_hash == "Yone"_FNV) {
        ChangeModelForObject(minion, "Yone", Object::self()->dataStack()->baseSkin.skin_id);
      } else if (skin_valid(hash)) {
        ChangeSkinForObject(minion, owner->dataStack()->baseSkin.skin_id);
      }
    } else if (is_companion(player_hash, hash)) {
      ChangeSkinForObject(minion, Object::self()->dataStack()->baseSkin.skin_id);
    }
  }
  for (const auto turret : span(ObjList::turrets()->data, ObjList::turrets()->size)) {
    if (const auto owner = turret->GetOwner(); owner == Object::self()) {
      ChangeSkinForObject(turret, Object::self()->dataStack()->baseSkin.skin_id);
    }
  }
}
