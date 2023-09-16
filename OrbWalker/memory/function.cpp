#include "stdafx.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23};  //jmp qword ptr[rbx]
void* trampoline = (void*)jmp_rbx_0;

namespace function {
using namespace offset;

float GameTime() { return *(float*)oGameTime; }

inline bool IsChatOpen() { return *(bool*)(*(uintptr_t*)oChatClient + 0xC90); }

inline bool IsLeagueInBackground() { return *(bool*)(*(uintptr_t*)oHudInstance + 0xB9); }

bool CanSendInput() { return script::self && script::self->IsAlive() && !(IsChatOpen() || IsLeagueInBackground()); }

void PrintMessage(std::string_view color, std::string_view text) {
  using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
  const auto wrapped = std::format("<font color={}>{}</font>", color, text);
  ((fnPrintChat)oPrintChat)(oChatClient, wrapped.data(), 4);
}

INT2 WorldToScreen(FLOAT3 in) {
  using fnWorldToScreen = uintptr_t(__fastcall*)(uintptr_t, FLOAT3*, FLOAT3*);
  FLOAT3 out;
  ((fnWorldToScreen)oWorldToScreen)(*(uintptr_t*)oViewPort + 0x270, &in, &out);
  return {(int)out.x, (int)out.y};
}

void AttackObject(Object* target) {
  using fnIssueOrder = bool(__fastcall*)(uintptr_t, int, bool, bool, int, int, bool);
  const auto pos = WorldToScreen(target->position());
  auto hudInput = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x48);
  fnIssueOrder IssueOrder = (fnIssueOrder)oIssueOrder;
  spoof_call(trampoline, IssueOrder, hudInput, 0, false, false, pos.x, pos.y, true);
}

void Move2Mouse() {
  using fnIssueMove = bool(__fastcall*)(uintptr_t, int, int, bool, bool, bool);
  if(POINT pos; GetCursorPos(&pos)) {
    auto hudInput = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x28);
    fnIssueMove IssueMove = (fnIssueMove)oIssueMove;
    spoof_call(trampoline, IssueMove, hudInput, (int)pos.x, (int)pos.y, false, true, true);
  }
}

bool CastSpell(Object* target, int index) {
  Object* self = script::self;
  auto spell = self->GetSpell(index);
  auto targetInfo = spell->spellInput();
  if(!targetInfo || !target) {
    return false;
  }
  uintptr_t InputLogic = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x68);

  // set spell position
  //targetInfo->SetCasterHandle(self->index());
  //targetInfo->SetTargetHandle(target->index());
  targetInfo->SetStartPos(self->position());
  targetInfo->SetEndPos(target->position());
  targetInfo->SetClickedPos(target->position());
  targetInfo->SetUnkPos(target->position());

  typedef void(__fastcall * fnHudCastSpell)(uintptr_t HudInput, uintptr_t SpellData);
  fnHudCastSpell HudCastSpell = (fnHudCastSpell)((uintptr_t)GetModuleHandle(nullptr) + 0x897870);
  spoof_call(trampoline, HudCastSpell, InputLogic, spell->spellInfo());

  return true;
}
}  // namespace function