#include "stdafx.hpp"

using namespace offset;

float GameTime() {
  if(!oGameTime) return 0.f;
  return *(float *)oGameTime;
}

bool IsChatOpen() {
  return *(bool *)(*(uintptr_t *)oChatClient + 0xC90);
}

bool IsLeagueInBackground() {
  return *(bool *)(*(uintptr_t *)oHudInstance + 0xB9);
}

void PrintMessage(std::string color, std::string text) {
  using fnPrintChat = void(__fastcall *)(uintptr_t, const char *, int);
  const auto wrapped = "<font color=" + color + '>' + text + "</font>";
  ((fnPrintChat)oPrintChat)(oChatClient, wrapped.data(), 4);
}

INT2 WorldToScreen(FLOAT3 in) {
  using fnWorldToScreen = bool(__fastcall *)(uintptr_t, FLOAT3 *, FLOAT3 *);
  FLOAT3 out;
  ((fnWorldToScreen)oWorldToScreen)(*(uintptr_t *)oViewPort + 0x270, &in, &out);
  return {(int)out.x, (int)out.y};
}

void Attack(Object *target) {
  using fnIssueOrder = int(__fastcall *)(uintptr_t, bool, int, int, int, int, int);
  auto headPos = target->position();
  headPos.y += target->height() / 2;
  const auto pos = WorldToScreen(headPos);
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x48);
  ((fnIssueOrder)oIssueOrder)(hudInput, false, 0, 1, pos.x, pos.y, 1);
}

void Move2Mouse() {
  using fnIssueMove = bool(__fastcall *)(uintptr_t, int, int, bool, int, int);
  if(POINT pos; GetCursorPos(&pos)) {
    auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x28);
    ((fnIssueMove)oIssueMove)(hudInput, pos.x, pos.y, false, 0, 1);
  }
}