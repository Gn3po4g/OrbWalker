#include "stdafx.hpp"

namespace ui {

  void Update() {
    using namespace config;
    if(ImGui::IsKeyPressed(menuKey)) {
      showMenu = !showMenu;
    }
    if(!showMenu) return;
    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    if(ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
      if(ImGui::BeginTabItem("Script")) {
        ImGui::Text("Targeting Setting:");
        ImGui::PushItemWidth(150);
        ImGui::Combo("Current Method", &targeting, TargetingStr.data(), (int)TargetingStr.size());
        ImGui::PopItemWidth();
        ImGui::Separator();
        ImGui::Text("Key Setting:");
        ImGui::HotKey("Kite Key", kiteKey);
        ImGui::HotKey("Clean Lane Key", cleanKey);
        ImGui::EndTabItem();
      }
      if(ImGui::BeginTabItem("Skin")) {
        ImGui::Text("Skin Setting:");
        static int temp{};
        const char *t[]{"coming soon"};
        ImGui::Combo("Current Skin", &temp, t, IM_ARRAYSIZE(t));
        ImGui::Separator();
        ImGui::Text("Key Setting:");
        ImGui::HotKey("Previous Skin Key", prevSkinKey);
        ImGui::HotKey("Next Skin Key", nextSkinKey);
        ImGui::EndTabItem();
      }

      if(ImGui::BeginTabItem("Extras")) {
        ImGui::HotKey("Menu Key", menuKey);
        ImGui::Separator();
        if(ImGui::Button("Force Close")) {
          ExitProcess(0u);
        }
        ImGui::EndTabItem();
      }
      ImGui::End();
    }
  }
}// namespace ui

namespace ImGui {
  bool SetToPressedKey(ImGuiKey &key) {
    for(int i = ImGuiKey::ImGuiKey_Tab; i < ImGuiKey::ImGuiKey_KeypadEqual + 1; ++i) {
      if(ImGui::IsKeyPressed(ImGuiKey(i))) {
        if(i == ImGuiKey_Escape) {
          key = ImGuiKey_None;
        } else {
          key = ImGuiKey(i);
        }
        return true;
      }
    }
    return false;
  }

  const char *ToString(ImGuiKey key) {
    if(key == ImGuiKey_None) {
      return "NONE";
    } else {
      return keyMap[key - ImGuiKey_Tab].data();
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
      if((!IsItemHovered() && GetIO().MouseClicked[0]) || SetToPressedKey(key)) {
        activeMap[id] = false;
      }
    } else if(Button(ToString(key), size)) {
      activeMap[id] = true;
    }
  }
}// namespace ImGui