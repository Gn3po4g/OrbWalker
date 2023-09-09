#include "stdafx.hpp"

namespace render {
  void RenderCircleWorld(const FLOAT3 &worldPos, float radius, uintptr_t color, float thickness) {
    ImGuiWindow *window = ImGui::GetCurrentWindow();

    float a = (float)((color >> 24) & 0xff);
    float r = (float)((color >> 16) & 0xff);
    float g = (float)((color >> 8) & 0xff);
    float b = (float)(color & 0xff);

    const int numPoints = 100;
    ImVec2 points[numPoints]{};
    float theta = 0.f;
    for(int i = 0; i < numPoints; i++, theta += IM_PI * 2 / numPoints) {
      FLOAT3 worldSpace = {worldPos.x + radius * cos(theta), worldPos.y, worldPos.z + radius * sin(theta)};
      ImVec2 screenSpace = WorldToScreen(worldSpace).ToImVec();
      points[i] = screenSpace;
    }
    window->DrawList->AddPolyline(points, numPoints, ImGui::GetColorU32({r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f}), true, thickness);
  }

  void DrawAttackRange() {
    const auto self = script::LocalPlayer();
    RenderCircleWorld(self->position(), self->RealAttackRange(), 0xffffffff, 1.0f);
  }

  void Update() {
    ImGuiIO &io = ImGui::GetIO();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0.0f, 0.0f, 0.0f, 0.0f});
    ImGui::Begin("drawingwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

    DrawAttackRange();

    ImGuiWindow *window = ImGui::GetCurrentWindow();
    window->DrawList->PushClipRectFullScreen();

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
  }
}// namespace render