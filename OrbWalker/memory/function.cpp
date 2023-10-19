#include "pch.hpp"

#include "function.hpp"
#include "global.hpp"
#include "offset.hpp"
#include "spoof_call.h"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]
void *trampoline = (void *)jmp_rbx_0;

namespace function {

float GameTime() { return *(float *)oGameTime; }

bool IsChatOpen() { return *(bool *)(*(uintptr_t *)oChatClient + 0xC90); }

bool IsLeagueInBackground() { return *(bool *)(*(uintptr_t *)oHudInstance + 0xB9); }

bool CanSendInput() { return self && self->IsAlive() && !(IsChatOpen() || IsLeagueInBackground()); }

void PrintMessage(size_t color, std::string_view msg) {
  const auto wrapped = std::format("<font color=#{:0>6x}>{}</font>", color & 0xFFFFFF, msg);
  call_function<void>(oPrintChat, oChatClient, wrapped.data(), 4);
}

INT2 WorldToScreen(FLOAT3 in) {
  FLOAT3 out;
  call_function<uintptr_t>(oWorldToScreen, *(uintptr_t *)oViewPort + 0x270, &in, &out);
  return {(int)out.x, (int)out.y};
}

void AttackObject(Object *target) {
  using fnIssueOrder = bool(__fastcall *)(uintptr_t, uint8_t, uint8_t, uint8_t, int, int, uint8_t);
  const auto pos = WorldToScreen(target->position());
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x48);
  spoof_call(trampoline, (fnIssueOrder)oIssueOrder, hudInput, 2ui8, 0ui8, 0ui8, pos.x, pos.y, 0ui8);
}

void Move2Mouse() {
  using fnIssueMove = bool(__fastcall *)(uintptr_t, int, int, uint8_t, uint8_t, uint8_t);
  if(POINT pos; GetCursorPos(&pos)) {
    auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x28);
    spoof_call(trampoline, (fnIssueMove)oIssueMove, hudInput, (int)pos.x, (int)pos.y, 0ui8, 0ui8, 1ui8);
  }
}

bool CastSpell(SpellSlot slot) {
  if(slot >= SpellSlot_Other) { return false; }
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(slot);
  auto targetInfo = spell->spellInput();
  if(!targetInfo) { return false; }
  // set spell position
  targetInfo->SetCasterHandle(self->index());
  targetInfo->SetTargetHandle(0);
  targetInfo->SetStartPos(self->position());
  targetInfo->SetEndPos(self->position());
  targetInfo->SetClickedPos(self->position());
  targetInfo->SetUnkPos(self->position());

  typedef void(__fastcall * fnHudCastSpell)(uintptr_t, uintptr_t);
  fnHudCastSpell HudCastSpell = (fnHudCastSpell)oCastSpell;
  spoof_call(trampoline, HudCastSpell, hudInput, spell->spellInfo());

  return true;
}

bool CastSpell(Object *target, SpellSlot slot) {
  if(slot >= SpellSlot_Other) { return false; }
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(slot);
  auto targetInfo = spell->spellInput();
  if(!targetInfo || !target) { return false; }
  // set spell position
  targetInfo->SetCasterHandle(self->index());
  targetInfo->SetTargetHandle(target->index());
  targetInfo->SetStartPos(self->position());
  targetInfo->SetEndPos(target->position());
  targetInfo->SetClickedPos(target->position());
  targetInfo->SetUnkPos(target->position());

  typedef void(__fastcall * fnHudCastSpell)(uintptr_t, uintptr_t);
  fnHudCastSpell HudCastSpell = (fnHudCastSpell)oCastSpell;
  spoof_call(trampoline, HudCastSpell, hudInput, spell->spellInfo());

  return true;
}

bool CastSpell(FLOAT3 pos, SpellSlot slot) {
  if(slot >= SpellSlot_Other) { return false; }
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(slot);
  auto targetInfo = spell->spellInput();
  if(!targetInfo) { return false; }
  // set spell position
  targetInfo->SetCasterHandle(self->index());
  targetInfo->SetTargetHandle(0);
  targetInfo->SetStartPos(self->position());
  targetInfo->SetEndPos(pos);
  targetInfo->SetClickedPos(pos);
  targetInfo->SetUnkPos(pos);

  typedef void(__fastcall * fnHudCastSpell)(uintptr_t, uintptr_t);
  fnHudCastSpell HudCastSpell = (fnHudCastSpell)oCastSpell;
  spoof_call(trampoline, HudCastSpell, hudInput, spell->spellInfo());
  return true;
}

void Draw(std::function<void()> draw_fun) {
  ImGuiIO &io = ImGui::GetIO();

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

void Circle(const FLOAT3 &worldPos, float radius, uint32_t color, float thickness) {
  ImGuiWindow *window = ImGui::GetCurrentWindow();
  const int numPoints = 127;
  ImVec2 points[numPoints]{};
  float theta = 0.f;
  for(int i = 0; i < numPoints; i++, theta += IM_PI * 2 / numPoints) {
    FLOAT3 worldSpace{worldPos.x + radius * cos(theta), worldPos.y, worldPos.z + radius * sin(theta)};
    ImVec2 screenSpace = WorldToScreen(worldSpace).ToImVec();
    points[i] = screenSpace;
  }
  window->DrawList->AddPolyline(points, numPoints, color, true, thickness);
}
} // namespace function