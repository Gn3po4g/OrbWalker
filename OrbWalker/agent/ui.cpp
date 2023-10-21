#include "pch.hpp"

#include "ui.hpp"

#include "agent/skinchanger.hpp"
#include "config/config.hpp"
#include "memory/global.hpp"
#include "memory/offset.hpp"

namespace ui {
auto vector_getter_skin = [](void *vec, const int32_t idx, const char **out_text) {
  const auto index = static_cast<size_t>(idx);
  const auto &v = *static_cast<std::vector<skin::SkinInfo> *>(vec);
  if(index >= v.size()) { return false; }
  *out_text = v[index].skinName.data();
  return true;
};

auto vector_getter_gear = [](void *vec, const int32_t idx, const char **out_text) {
  const auto index = static_cast<size_t>(idx);
  const auto &v = *static_cast<std::vector<std::string> *>(vec);
  if(index >= v.size()) { return false; }
  *out_text = v[index].data();
  return true;
};

auto selector_getter = [](void *vec, const int32_t idx, const char **out_text) {
  switch(idx) {
  case health_lowest:
    *out_text = "health_lowest";
    break;
  case distance_closest:
    *out_text = "distance_closest";
    break;
  case health_percent_lowest:
    *out_text = "health_percent_lowest";
    break;
  default:
    return false;
  }
  return true;
};

void Update() {
  static int gear{};
  static bool show_menu{true};
  auto &config = config::inst();
  if(ImGui::IsKeyPressed(config.menu_key)) { show_menu ^= true; }
  if(!show_menu) return;
  ImGui::Begin(
    "Settings", nullptr,
    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
      | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing
  );
  if(ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
    if(ImGui::BeginTabItem("Script")) {
      ImGui::Text("Drawing Setting:");
      ImGui::Checkbox("Show Attack Range", &config.show_attack_range);
      ImGui::Separator();
      ImGui::Text("Selector Setting:");
      //ImGui::PushItemWidth(150);
      ImGui::Combo("##Current Method", &config.selector, selector_getter, nullptr, count);
      //ImGui::PopItemWidth();
      ImGui::Separator();
      ImGui::Text("Key Setting:");
      ImGui::HotKey("Kite Key", config.kite_key);
      ImGui::HotKey("Clean Lane Key", config.clean_key);
      ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Skin")) {
      ImGui::Text("Skin Setting:");
      auto &skins{skin::inst().championsSkins};
      size_t max_len{};
      for(auto &skin_info : skins) max_len = std::max(max_len, skin_info.skinName.size());
      ImGui::Text("Current Skin");
      if(ImGui::Combo("##Current Skin", &config.current_skin, vector_getter_skin, &skins, (int)skins.size())) {
        skin::inst().ChangeSkin(skins[config.current_skin].modelName, skins[config.current_skin].skinId);
        config.save();
      }
      // ImGui::PopItemWidth();
      const auto player_hash{FNV(self->dataStack()->baseSkin.model.str())};
      if(const auto it{std::ranges::find_if(
           skin::inst().specialSkins,
           [player_hash](const skin::SpecialSkin &x) {
             const auto skin_id = self->dataStack()->baseSkin.skin_id;
             return x.champName == player_hash && (x.skinIdStart <= skin_id && x.skinIdEnd >= skin_id);
           }
         )};
         it != skin::inst().specialSkins.end()) {
        const auto stack{self->dataStack()};
        gear = static_cast<int>(stack->baseSkin.gear);
        ImGui::Text("Current Gear");
        if(ImGui::Combo("##Current Gear", &gear, vector_getter_gear, &it->gears, (int)it->gears.size())) {
          stack->baseSkin.gear = static_cast<int8_t>(gear);
          stack->update(true);
        }
      }
      ImGui::Separator();
      ImGui::Text("Key Setting:");
      ImGui::HotKey("Previous Skin Key", config.prev_skin_key);
      ImGui::HotKey("Next Skin Key", config.next_skin_key);
      ImGui::EndTabItem();
    }

    // if(ImGui::BeginTabItem("Infos")) {
    //   auto FindVtFunction = [](const DWORD64 Fn_address) {
    //     DWORD64 *base = *reinterpret_cast<DWORD64 **>(self);
    //     int i = 0;
    //     while(base[i]) {
    //       if(base[i] == Fn_address) {
    //         ImGui::Text("Found VT function at %d", i);
    //         return i;
    //       }
    //       i++;
    //     }
    //     ImGui::Text("VT Function not found %d", i);
    //     return -1;
    //   };
    //   FindVtFunction(oBonusRadius);
    //   //FindVtFunction(oAttackWindup);
    //   ImGui::EndTabItem();
    // }

    if(ImGui::BeginTabItem("Extras")) {
      ImGui::HotKey("Menu Key", config.menu_key);
      ImGui::Separator();
      if(ImGui::Button("Force Close")) { std::terminate(); }
      ImGui::EndTabItem();
    }
    ImGui::End();
  }
  ImGui::End();
}
} // namespace ui

namespace ImGui {
bool SetToPressedKey(ImGuiKey &key) {
  for(const auto &key_in_map : keyMap | std::views::keys) {
    if(IsKeyPressed(key_in_map)) {
      if(key_in_map == ImGuiKey_Escape) key = ImGuiKey_None;
      else key = key_in_map;
      return true;
    }
  }
  return false;
}

void HotKey(const char *label, ImGuiKey &key, const ImVec2 &size) {
  static std::map<ImGuiID, bool> activeMap;
  const auto id = GetID(label);
  AlignTextToFramePadding();
  Text(label);
  SameLine(150.f);
  if(activeMap[id]) {
    PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
    Button("...", size);
    PopStyleColor();
    if((!IsItemHovered() && GetIO().MouseClicked[0]) || SetToPressedKey(key)) { activeMap[id] = false; }
  } else if(Button(keyMap[key].data(), size)) {
    activeMap[id] = true;
  }
}
} // namespace ImGui