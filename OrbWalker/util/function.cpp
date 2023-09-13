#include "stdafx.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23};//jmp qword ptr[rbx]
void *trampoline = (void*)jmp_rbx_0;

using namespace offset;
namespace function {


  float GameTime() {
    if(!oGameTime) return 0.f;
    return *(float *)oGameTime;
  }

  inline bool IsChatOpen() {
    return *(bool *)(*(uintptr_t *)oChatClient + 0xC90);
  }

  inline bool IsLeagueInBackground() {
    return *(bool *)(*(uintptr_t *)oHudInstance + 0xB9);
  }

  bool CanSendInput() {
    return script::self && script::self->IsAlive() &&
           !(IsChatOpen() || IsLeagueInBackground());
  }

  void PrintMessage(std::string_view color, std::string_view text) {
    using fnPrintChat = void(__fastcall *)(uintptr_t, const char *, int);
    const auto wrapped = std::format("<font color={}>{}</font>", color, text);
    ((fnPrintChat)oPrintChat)(oChatClient, wrapped.data(), 4);
  }

  INT2 WorldToScreen(FLOAT3 in) {
    using fnWorldToScreen = uintptr_t(__fastcall *)(uintptr_t, FLOAT3 *, FLOAT3 *);
    FLOAT3 out;
    ((fnWorldToScreen)oWorldToScreen)(*(uintptr_t *)oViewPort + 0x270, &in, &out);
    return {(int)out.x, (int)out.y};
  }

  void AttackObject(Object *target) {
    using fnIssueOrder = bool(__fastcall *)(uintptr_t, int, bool, bool, int, int, bool);
    auto headPos = target->position();
    headPos.y += target->scale() * target->characterdata()->size() * .9f;
    const auto pos = WorldToScreen(headPos);
    auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x48);
    fnIssueOrder IssueOrder = (fnIssueOrder)oIssueOrder;
    spoof_call(trampoline, IssueOrder, hudInput, 0, false, true, pos.x, pos.y, true);
  }

  void Move2Mouse() {
    using fnIssueMove = bool(__fastcall *)(uintptr_t, int, int, bool, bool, bool);
    if(POINT pos; GetCursorPos(&pos)) {
      auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x28);
      fnIssueMove IssueMove = (fnIssueMove)oIssueMove;
      spoof_call(trampoline, IssueMove, hudInput, (int)pos.x, (int)pos.y, false, false, true);
    }
  }
}// namespace function