#include "pch.hpp"

#include "render.hpp"

#include "agent/orb.hpp"
#include "config/config.hpp"
#include "memory/function.hpp"

#include "render.hpp"

#include "agent/orb.hpp"
#include "config/config.hpp"
#include "memory/function.hpp"

namespace render {
void RenderCircleWorld(const FLOAT3 &worldPos, float radius, uint32_t color, float thickness) {
  ImGuiWindow *window = ImGui::GetCurrentWindow();
  const int numPoints = 100;
  ImVec2 points[numPoints]{};
  float theta = 0.f;
  for(int i = 0; i < numPoints; i++, theta += IM_PI * 2 / numPoints) {
    FLOAT3 worldSpace = {worldPos.x + radius * cos(theta), worldPos.y, worldPos.z + radius * sin(theta)};
    ImVec2 screenSpace = function::WorldToScreen(worldSpace).ToImVec();
    points[i] = screenSpace;
  }
  window->DrawList->AddPolyline(points, numPoints, color, true, thickness);
}

void DrawAttackRange() {
  if(!config::showAttackRange) return;
  const auto self = orb->self;
  RenderCircleWorld(self->position(), orb->script->draw_range(), 0xffffffff, 1.f);
}

void DrawMarkedObject() {
  const auto obj = orb->markedObject;
  if(!obj) return;
  RenderCircleWorld(obj->position(), obj->BonusRadius(), 0xff0c9d00, 5.f);
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
  DrawMarkedObject();

  ImGuiWindow *window = ImGui::GetCurrentWindow();
  window->DrawList->PushClipRectFullScreen();

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);
}
} // namespace render