#include "pch.hpp"

#include "function.hpp"
#include "offset.hpp"

#include "agent/hook.hpp"
#include "class/hud.hpp"
#include "config/config.hpp"

namespace function {
void *swap_chain() { return Read<void *>(call_function<uptr>(RVA(oMaterialRegistry)) + 0x1C0); }

float GameTime() { return Read<float>(RVA(oGameTime)); }

float ping() { return call_function<u64>(RVA(oGetPing), Read<uptr>(RVA(oPingNet))) / 1000.f; }

GameState game_state() {
  // auto addr = Read<uptr>(RVA(oGameState));
  // return addr ? Read<GameState>(addr + 0xC) : Loading;
  return GameTime() > 1.f ? Running : Loading;
}

bool IsChatOpen() { return Read<bool>(Read<uptr>(RVA(oChatClient)) + 0xC90); }

vec2 WorldToScreen(const vec3 &in) {
  const matrix view_matrix = Read<matrix>(RVA(oViewProjMatrix));
  const matrix proj_matrix = Read<matrix>(RVA(oViewProjMatrix) + 0x40);
  const Viewport viewport  = Read<Viewport>(RVA(oViewProjMatrix) + 0x8C);

  auto res = viewport.project(in, proj_matrix, view_matrix);
  return {res.x, res.y};
}

void AttackObject(Object *target) {
  const auto order = Hud::inst().hud_order();
  const auto pos   = screen_pos(WorldToScreen(target->position()));
  call_function<void>(RVA(oIssueOrder), order, 0, 2, 0, pos.x, pos.y, 2);
}

void Move2Mouse() {
  const auto mouse          = Hud::inst().hud_mouse();
  const screen_pos pos      = mouse->mouse_screen_pos();
  mouse->mouse_last_world() = {0.f, 0.f, 0.f};
  call_function<void>(RVA(oIssueMove), mouse, pos.x, pos.y, 0, 0, config::inst().show_click);
}

void PressKeyAt(SpellSlot spell_slot, const vec3 &pos) {
  // auto CreateKeyboardInput = [](WORD vkCode, bool down) {
  //   INPUT input{};
  //   input.type       = INPUT_KEYBOARD;
  //   input.ki.wVk     = vkCode;
  //   input.ki.wScan   = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
  //   input.ki.dwFlags = KEYEVENTF_SCANCODE | (down ? 0 : KEYEVENTF_KEYUP);
  //   return input;
  // };
  // auto PressKey = [&](WORD key) {
  //   INPUT inputs[2]{CreateKeyboardInput(key, true), CreateKeyboardInput(key, false)};
  //   SendInput(2, inputs, sizeof(INPUT));
  // };
  ////221BE78
  // const auto screen_pos = WorldToScreen(pos);
  // hook::MousePos        = {static_cast<long>(screen_pos.x), static_cast<long>(screen_pos.y)};
  // PressKey(key);
  const auto cast         = Hud::inst().hud_cast();
  const auto spell_info   = Object::self()->GetSpell(spell_slot)->spell_info();
  auto &mouse_pos         = Hud::inst().hud_mouse()->mouse_screen_pos();
  const screen_pos origin = mouse_pos;
  mouse_pos               = WorldToScreen(pos);
  call_function<void>(RVA(0x8C5010), cast, spell_info, 0);
  Read<vec3>((uptr)cast + 0x2C) = pos;
  call_function<void>(RVA(0x8C5010), cast, spell_info, 1);
  mouse_pos = origin;
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

  ImGui::GetWindowDrawList()->PushClipRectFullScreen();

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);
}

void Circle(const vec3 &center, float radius, u32 color, float thickness) {
  const size_t numPoints{314};
  ImVec2 points[numPoints]{};
  float theta{0.f};
  for (size_t i{0}; i < numPoints; i++) {
    vec3 world_pos(center.x + radius * cos(theta), center.y, center.z + radius * sin(theta));
    const auto screen_pos = WorldToScreen(world_pos);
    points[i]             = {screen_pos.x, screen_pos.y};
    theta += IM_PI * 2 / numPoints;
  }
  ImGui::GetWindowDrawList()->AddPolyline(points, numPoints, color, true, thickness);
}
} // namespace function