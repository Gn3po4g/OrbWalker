#include "pch.hpp"

#include "ui.hpp"

#include "agent/skinchanger.hpp"
#include "class/obj_list.hpp"
#include "class/object.hpp"
#include "config/config.hpp"

namespace ui {
auto vector_getter_skin = [](void *vec, const int32_t idx, const char **out_text) {
  const auto index = static_cast<size_t>(idx);
  const auto &v    = *static_cast<std::vector<skin::SkinInfo> *>(vec);
  if (index >= v.size()) { return false; }
  *out_text = v[index].skinName.data();
  return true;
};

auto vector_getter_gear = [](void *vec, const int32_t idx, const char **out_text) {
  const auto index = static_cast<size_t>(idx);
  const auto &v    = *static_cast<std::vector<std::string> *>(vec);
  if (index >= v.size()) { return false; }
  *out_text = v[index].data();
  return true;
};

auto selector_getter = [](void *_, const int32_t idx, const char **out_text) {
  if (idx >= selector_map.size()) { return false; }
  *out_text = selector_map.at(idx).data();
  return true;
};

void Update() {
  static int gear{};
  static bool show_menu{true};
  auto &config = config::inst();
  if (ImGui::IsKeyPressed(config.menu_key)) { show_menu ^= true; }
  if (!show_menu) return;
  ImGui::Begin(
    "Settings", nullptr,
    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
      | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing
  );
  if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
    if (ImGui::BeginTabItem("Script")) {
      ImGui::Text("Drawing Setting:");
      if (ImGui::Checkbox("Show Attack Range", &config.show_attack_range)) config.save();
      if (ImGui::Checkbox("Show Click", &config.show_click)) config.save();
      ImGui::Separator();
      ImGui::Text("Selector Setting:");
      if (ImGui::Combo("##Current Method", &config.selector, selector_getter, nullptr, count)) config.save();
      ImGui::Separator();
      ImGui::Text("Key Setting:");
      if (ImGui::HotKey("Kite Key", config.kite_key)) config.save();
      if (ImGui::HotKey("Clean Lane Key", config.clean_key)) config.save();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Skin")) {
      ImGui::Text("Skin Setting:");
      auto &skins{skin::inst().championsSkins};
      ImGui::Text("Current Skin");
      if (ImGui::Combo("##Current Skin", &config.current_skin, vector_getter_skin, &skins, (int)skins.size())) {
        skin::inst().ChangeSkin(skins[config.current_skin].modelName, skins[config.current_skin].skinId);
        config.save();
      }
      const auto player_hash{FNV(Object::self()->dataStack()->baseSkin.model.str())};
      if (const auto it{std::ranges::find_if(
            skin::inst().specialSkins,
            [player_hash](const skin::SpecialSkin &x) {
              const auto skin_id = Object::self()->dataStack()->baseSkin.skin_id;
              return x.champName == player_hash && (x.skinIdStart <= skin_id && x.skinIdEnd >= skin_id);
            }
          )};
          it != skin::inst().specialSkins.end()) {
        const auto stack{Object::self()->dataStack()};
        gear = static_cast<int>(stack->baseSkin.gear);
        ImGui::Text("Current Gear");
        if (ImGui::Combo("##Current Gear", &gear, vector_getter_gear, &it->gears, (int)it->gears.size())) {
          stack->baseSkin.gear = static_cast<int8_t>(gear);
          stack->update(true);
        }
      }
      ImGui::Separator();
      ImGui::Text("Key Setting:");
      if (ImGui::HotKey("Previous Skin Key", config.prev_skin_key)) config.save();
      if (ImGui::HotKey("Next Skin Key", config.next_skin_key)) config.save();
      ImGui::EndTabItem();
    }

    // if (ImGui::BeginTabItem("Infos")) {
    //   for (const auto minion : std::span(minions->data, minions->size)) {
    //       if (minion->position()-self->position() < 300.f)
    //       ImGui::Text(minion->name().data());
    //   }
    //   ImGui::EndTabItem();
    // }

    if (ImGui::BeginTabItem("Extras")) {
      if (ImGui::HotKey("Menu Key", config.menu_key)) config.save();
      ImGui::Separator();
      if (ImGui::Button("Force Close")) { std::terminate(); }
      ImGui::EndTabItem();
    }
    ImGui::End();
  }
  ImGui::End();
}
} // namespace ui

namespace ImGui {
bool SetToPressedKey(ImGuiKey &key) {
  for (const auto &key_in_map : keyMap | std::views::keys) {
    if (IsKeyPressed(key_in_map)) {
      if (key_in_map == ImGuiKey_Escape) key = ImGuiKey_None;
      else key = key_in_map;
      return true;
    }
  }
  return false;
}

bool HotKey(const char *label, ImGuiKey &key, const ImVec2 &size) {
  static std::map<ImGuiID, bool> activeMap;
  const auto id = GetID(label);
  AlignTextToFramePadding();
  Text(label);
  SameLine(150.f);
  if (activeMap[id]) {
    PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
    Button("...", size);
    PopStyleColor();
    if ((!IsItemHovered() && GetIO().MouseClicked[0]) || SetToPressedKey(key)) {
      activeMap[id] = false;
      return true;
    }
  } else if (Button(keyMap[key].data(), size)) {
    activeMap[id] = true;
  }
  return false;
}
} // namespace ImGui