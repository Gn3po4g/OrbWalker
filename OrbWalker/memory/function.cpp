#include "pch.hpp"

#include "function.hpp"
#include "offset.hpp"

#include "agent/hook.hpp"
#include "config/config.hpp"

namespace function {
void *swap_chain() { return Read<void *>(call_function<uptr>(RVA(oMaterialRegistry)) + 0x1C0); }

float GameTime() { return Read<float>(RVA(oGameTime)); }

GameState game_state() {
  auto addr = Read<uptr>(RVA(oGameState));
  return addr ? Read<GameState>(addr + 0xC) : Loading;
}

bool IsChatOpen() { return Read<bool>(Read<uptr>(RVA(oChatClient)) + 0xC90); }

bool IsLeagueInBackground() { return Read<bool>(Read<uptr>(RVA(oHudInstance)) + 0xB9); }

bool CanSendInput() { return Object::self()->IsAlive() && !(IsChatOpen() || IsLeagueInBackground()); }

vec2 WorldToScreen(const vec3 &in) {
  const auto view_matrix = Read<matrix>(RVA(oViewProjMatrix));
  const auto proj_matrix = Read<matrix>(RVA(oViewProjMatrix) + 0x40);
  const auto viewport    = Read<Viewport>(RVA(oViewProjMatrix) + 0x8C);

  auto res = viewport.project(in, proj_matrix, view_matrix);
  return vec2(res.x, res.y);
}

void AttackObject(Object *target) {
  const auto pos = WorldToScreen(target->position());
  auto hudInput  = Read<uptr>(Read<uptr>(RVA(oHudInstance)) + 0x48);
  call_function<bool>(
    RVA(oIssueOrder), hudInput, 2ui8, 0ui8, 0ui8, static_cast<int>(pos.x), static_cast<int>(pos.y), 1ui8
  );
}

void Move2Mouse() {
  if (POINT pos; GetCursorPos(&pos)) {
    auto hudInput              = Read<uptr>(Read<uptr>(RVA(oHudInstance)) + 0x28);
    *(vec3 *)(hudInput + 0x38) = vec3(0.f, 0.f, 0.f);
    call_function<bool>(RVA(oIssueMove), hudInput, pos.x, pos.y, 0ui8, 0ui8, config::inst().show_click);
  }
}

void PressKeyAt(WORD key, const vec3 &pos) {
  auto CreateKeyboardInput = [](WORD vkCode, bool down) {
    INPUT input{};
    input.type       = INPUT_KEYBOARD;
    input.ki.wVk     = vkCode;
    input.ki.wScan   = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
    input.ki.dwFlags = KEYEVENTF_SCANCODE | (down ? 0 : KEYEVENTF_KEYUP);
    return input;
  };
  auto PressKey = [&](WORD key) {
    INPUT inputs[2]{CreateKeyboardInput(key, true), CreateKeyboardInput(key, false)};
    SendInput(2, inputs, sizeof(INPUT));
  };
  hook::MousePos = WorldToScreen(pos);
   PressKey(key);
}

void Draw(std::function<void()> draw_fun) {
  ImGuiIO &io{ImGui::GetIO()};

  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
  ImGui::PushStyleColor(ImGuiCol_WindowBg, {0.0f, 0.0f, 0.0f, 0.0f});
  ImGui::Begin("drawingwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

  ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

  draw_fun();

  ImGuiWindow *window = ImGui::GetCurrentWindow();
  window->DrawList->PushClipRectFullScreen();

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);
}

void Circle(const vec3 &center, float radius, u32 color, float thickness) {
  ImGuiWindow *window{ImGui::GetCurrentWindow()};
  const size_t numPoints{314};
  ImVec2 points[numPoints]{};
  float theta{0.f};
  for (size_t i{0}; i < numPoints; i++) {
    vec3 world_pos(center.x + radius * cos(theta), center.y, center.z + radius * sin(theta));
    const auto screen_pos = WorldToScreen(world_pos);
    points[i]             = {screen_pos.x, screen_pos.y};
    theta += IM_PI * 2 / numPoints;
  }
  window->DrawList->AddPolyline(points, numPoints, color, true, thickness);
}
} // namespace function