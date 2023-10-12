#include "pch.hpp"

#include "ui.hpp"

#include "agent/skinchanger.hpp"
#include "config/config.hpp"
#include "memory/global.hpp"

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
  default:
    return false;
  }
  return true;
};

void LoadTheme() {
  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(8.00f, 8.00f);
  style.FramePadding = ImVec2(5.00f, 2.00f);
  style.CellPadding = ImVec2(6.00f, 6.00f);
  style.ItemSpacing = ImVec2(6.00f, 6.00f);
  style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
  style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
  style.IndentSpacing = 25;
  style.ScrollbarSize = 15;
  style.GrabMinSize = 10;
  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 1;
  style.TabBorderSize = 1;
  style.WindowRounding = 7;
  style.ChildRounding = 4;
  style.FrameRounding = 3;
  style.PopupRounding = 4;
  style.ScrollbarRounding = 9;
  style.GrabRounding = 3;
  style.LogSliderDeadzone = 4;
  style.TabRounding = 4;
}

void Update() {
  static int gear{};
  auto &config = config::inst();
  if(ImGui::IsKeyPressed(config.menu_key)) { config.show_menu ^= true; }
  if(!config.show_menu) { return; }
  ImGui::Begin(
    "Settings",
    nullptr,
    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
      | ImGuiWindowFlags_AlwaysAutoResize
  );
  if(ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
    if(ImGui::BeginTabItem("Script")) {
      ImGui::Text("Drawing Setting:");
      ImGui::Checkbox("Show Attack Range", &config.show_attack_range);
      ImGui::Separator();
      ImGui::Text("Selector Setting:");
      ImGui::PushItemWidth(150);
      ImGui::Combo("Current Method", &config.selector, selector_getter, nullptr, count);
      ImGui::PopItemWidth();
      ImGui::Separator();
      ImGui::Text("Key Setting:");
      ImGui::HotKey("Kite Key", config.kite_key);
      ImGui::HotKey("Clean Lane Key", config.clean_key);
      ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Skin")) {
      ImGui::Text("Skin Setting:");
      auto &skins{skin::inst().championsSkins};
      if(ImGui::Combo("Current Skin", &config.current_skin, vector_getter_skin, &skins, (int)skins.size())) {
        skin::inst().ChangeSkin(skins[config.current_skin].modelName, skins[config.current_skin].skinId);
        config::inst().save();
      }
      const auto player_hash{FNV(self->dataStack()->baseSkin.model)};
      if(const auto it{std::ranges::find_if(
           skin::inst().specialSkins,
           [player_hash](const skin::SpecialSkin &x) {
             const auto skin_id = self->dataStack()->baseSkin.skin_id;
             return x.champHash == player_hash && (x.skinIdStart <= skin_id && x.skinIdEnd >= skin_id);
           }
         )};
         it != skin::inst().specialSkins.end()) {
        const auto stack{self->dataStack()};
        gear = static_cast<int>(stack->baseSkin.gear);

        if(ImGui::Combo("Current Gear", &gear, vector_getter_gear, &it->gears, (int)it->gears.size())) {
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
// #define UI_DEBUG
#ifdef UI_DEBUG
    if(ImGui::BeginTabItem("Infos")) {
      ImGui::LabelText("##GameTime", "GameTime: %fs", function::GameTime());
      ImGui::LabelText("##LocalPlayer", "LocalPlayer: %p", self);
      ImGui::LabelText("##name", "name: %s", self->name().data());
      // const auto time = function::GameTime();
      for(auto buff : self->buffs()) {
        if(buff->name() != "" && buff->starttime() <= function::GameTime() && buff->endtime() >= function::GameTime())
          ImGui::LabelText(("##buff" + buff->name()).data(), "%s", buff->name().data());
      }

      ImGui::EndTabItem();
    }
#endif
    if(ImGui::BeginTabItem("Extras")) {
      ImGui::HotKey("Menu Key", config.menu_key);
      ImGui::Separator();
      if(ImGui::Button("Force Close")) { std::terminate(); }
      ImGui::EndTabItem();
    }
    ImGui::End();
  }
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

const char *ToString(const ImGuiKey &key) {
  if(key == ImGuiKey_None) {
    return "NONE";
  } else {
    return keyMap[key].data();
  }
}

void HotKey(const char *label, ImGuiKey &key, const ImVec2 &size) {
  static std::map<ImGuiID, bool> activeMap;
  const auto id = GetID(label);
  PushItemWidth(150);
  LabelText(("##"s + label).data(), label);
  PopItemWidth();
  SameLine();
  if(activeMap[id]) {
    PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
    Button("...", size);
    PopStyleColor();
    if((!IsItemHovered() && GetIO().MouseClicked[0]) || SetToPressedKey(key)) { activeMap[id] = false; }
  } else if(Button(ToString(key), size)) {
    activeMap[id] = true;
  }
}
} // namespace ImGui