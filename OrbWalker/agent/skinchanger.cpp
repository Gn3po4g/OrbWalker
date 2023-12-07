#include "pch.hpp"

#include "skinchanger.hpp"

#include "class/champion.hpp"
#include "config/config.hpp"
#include "memory/offset.hpp"

#include "memory/function.hpp"
#include <class/obj_list.hpp>

using namespace std;

bool skin_valid(string_view minion_name) {
  switch (FNV(minion_name)) {
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

bool is_companion(string_view owner, string_view obj) {
  switch (FNV(owner)) {
  case "Kindred"_FNV:
    return obj == "KindredWolf";
  case "Nunu"_FNV:
    return obj == "NunuSnowball";
  case "Quinn"_FNV:
    return obj == "QuinnValor";
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
    const auto champName{stack->baseSkin.model.str()};
    if (std::ranges::count_if(specialSkins, [&](const SpecialSkin &special_skin) {
          return special_skin.champName == champName && skin_id >= special_skin.skinIdStart
              && skin_id <= special_skin.skinIdEnd;
        })) {
      // stack->stack.clear();
      stack->baseSkin.gear = 0;
      stack->update(true);
    } else if (champName == "Lux" && skin_id == 7 || champName == "Sona" && skin_id == 6) {
      stack->stack.clear();
      stack->push(model.data(), skin_id);
    } else if (champName != "Kayn") {
      stack->baseSkin.gear = static_cast<int8_t>(-1);
      stack->update(true);
    }
  };
  const auto stack{Object::self()->dataStack()};
  ((xor_value<i32> *)((uptr)Object::self() + objSkinId))->encrypt(skin_id);
  stack->baseSkin.skin_id = skin_id;
  CheckSpecialSkins(model, skin_id);
}

std::vector<std::string> skin::skins_name() {
  return championSkins | views::transform([](const SkinInfo &si) { return si.skinName; }) | ranges::to<vector>();
}

i64 skin::special_skin() {
  const auto baseSkin{Object::self()->dataStack()->baseSkin};
  return distance(specialSkins.begin(), std::ranges::find_if(specialSkins, [baseSkin](const skin::SpecialSkin &x) {
                    return x.champName == baseSkin.model.str()
                        && (x.skinIdStart <= baseSkin.skin_id && x.skinIdEnd >= baseSkin.skin_id);
                  }));
}

skin &skin::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(new skin()); });
  return *instance_;
}

skin::skin() {
  const auto default_skin = Object::self()->dataStack()->baseSkin;
  championSkins.emplace_back(default_skin.model.str(), "Default", default_skin.skin_id);
  const auto champions = Read<vector<Champion *>>(Read<uintptr_t>(RVA(oChampionManager)) + 0x18);
  if (const auto it{ranges::find_if(
        champions, [](Champion *champion) { return Object::self()->name() == champion->championName().str(); }
      )};
      it != champions.end()) {
    const auto champion = *it;
    auto skins_id       = champion->skins_id();
    map<string, i32> tempSkinList;
    for (auto &i : skins_id) {
      const auto name = champion->championName().str();
      const auto game_name =
        i ? format("game_character_skin_displayname_{}_{}", name, i) : format("game_character_displayname_{}", name);
      auto translatedName = string(call_function<const char *>(RVA(oTranslateString), game_name.data()));
      if (tempSkinList.count(translatedName)) {
        translatedName.append(format(" Chroma {}", tempSkinList[translatedName]++));
      } else {
        tempSkinList[translatedName] = 1;
      }
      championSkins.emplace_back(name, translatedName, i);
      if (i == 7 && name == "Lux") {
        championSkins.emplace_back("LuxAir", "Elementalist Air Lux", i);
        championSkins.emplace_back("LuxDark", "Elementalist Dark Lux", i);
        championSkins.emplace_back("LuxFire", "Elementalist Fire Lux", i);
        championSkins.emplace_back("LuxIce", "Elementalist Ice Lux", i);
        championSkins.emplace_back("LuxMagma", "Elementalist Magma Lux", i);
        championSkins.emplace_back("LuxMystic", "Elementalist Mystic Lux", i);
        championSkins.emplace_back("LuxNature", "Elementalist Nature Lux", i);
        championSkins.emplace_back("LuxStorm", "Elementalist Storm Lux", i);
        championSkins.emplace_back("LuxWater", "Elementalist Water Lux", i);
      } else if (i == 6 && name == "Sona") {
        championSkins.emplace_back("SonaDJGenre02", "DJ Sona 2", i);
        championSkins.emplace_back("SonaDJGenre03", "DJ Sona 3", i);
      }
    }
  }
}

void skin::update() {
  auto &config = config::inst();
  static std::once_flag init_skin;
  std::call_once(init_skin, [&] {
    if (config.current_skin > 0) {
      auto index = std::min((size_t)config.current_skin, championSkins.size());
      const auto &[modelName, skinName, skinId]{championSkins[index]};
      ChangeSkin(modelName, skinId);
    }
  });
  const auto player = Object::self()->dataStack()->baseSkin.model.str();
  if (ImGui::IsKeyPressed(ImGuiKey_5) && ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
    if (const auto i = special_skin(); (size_t)i < specialSkins.size()) {
      const auto stack     = Object::self()->dataStack();
      stack->baseSkin.gear = (stack->baseSkin.gear + 1) % specialSkins[i].gears.size();
      stack->update(true);
    }
  }
  if (ImGui::IsKeyPressed(config.prev_skin_key)) {
    config.current_skin                       = std::max(config.current_skin - 1, 0);
    const auto &[modelName, skinName, skinId] = championSkins[config.current_skin];
    ChangeSkin(modelName, skinId);
    config.save();
  } else if (ImGui::IsKeyPressed(config.next_skin_key)) {
    config.current_skin = std::min(config.current_skin + 1, static_cast<int>(championSkins.size() - 1));
    const auto &[modelName, skinName, skinId] = championSkins[config.current_skin];
    ChangeSkin(modelName, skinId);
    config.save();
  }
  if (!Object::self()->dataStack()->stack.empty()) {
    if (player != "Viego" && player != "Sylas") {
      if (auto &[model, _1, skin_id, _2, gear, _3] = Object::self()->dataStack()->stack.front();
          skin_id != Object::self()->dataStack()->baseSkin.skin_id) {
        skin_id = Object::self()->dataStack()->baseSkin.skin_id;
        Object::self()->dataStack()->update(true);
      }
    }
  }
  for (const auto minion : ObjList::minions()->all()) {
    const auto minion_name{minion->dataStack()->baseSkin.model.str()};
    if (const auto owner{minion->GetOwner()}; owner == Object::self()) {
      if (minion_name == "TestCubeRender10Vision" && player == "Yone") {
        ChangeModelForObject(minion, "Yone", Object::self()->dataStack()->baseSkin.skin_id);
      } else if (skin_valid(minion_name)) {
        ChangeSkinForObject(minion, owner->dataStack()->baseSkin.skin_id);
      }
    } else if (is_companion(player, minion_name)) {
      ChangeSkinForObject(minion, Object::self()->dataStack()->baseSkin.skin_id);
    }
  }
  for (const auto turret : ObjList::turrets()->all()) {
    if (const auto owner = turret->GetOwner(); owner == Object::self()) {
      ChangeSkinForObject(turret, Object::self()->dataStack()->baseSkin.skin_id);
    }
  }
}
