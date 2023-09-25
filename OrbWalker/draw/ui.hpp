#pragma once

namespace ui {
  void Update();
}// namespace ui

namespace ImGui {
  void HotKey(const char *label, ImGuiKey &key, const ImVec2 &size = {100.0f, 0.0f});
}