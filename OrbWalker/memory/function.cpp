#include "pch.hpp"

#include "function.hpp"
#include "global.hpp"
#include "offset.hpp"
#include "spoofcall.h"

#include "agent/orb.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]
void *trampoline = (void *)jmp_rbx_0;

namespace function {

float GameTime() { return *(float *)oGameTime; }

inline bool IsChatOpen() { return *(bool *)(*(uintptr_t *)oChatClient + 0xC90); }

inline bool IsLeagueInBackground() { return *(bool *)(*(uintptr_t *)oHudInstance + 0xB9); }

bool CanSendInput() { return self->IsAlive() && !(IsChatOpen() || IsLeagueInBackground()); }

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
  using fnIssueOrder = bool(__fastcall *)(uintptr_t, int64_t, uint8_t, char, int, int, char);
  const auto pos = WorldToScreen(target->position());
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x48);
  fnIssueOrder IssueOrder = (fnIssueOrder)oIssueOrder;
  spoof_call(trampoline, IssueOrder, hudInput, 2ll, (uint8_t)0, '\1', pos.x, pos.y, '\0');
}

void Move2Mouse() {
  using fnIssueMove = bool(__fastcall *)(uintptr_t, int, int, bool, bool, bool);
  if(POINT pos; GetCursorPos(&pos)) {
    auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x28);
    fnIssueMove IssueMove = (fnIssueMove)oIssueMove;
    spoof_call(trampoline, IssueMove, hudInput, (int)pos.x, (int)pos.y, false, true, true);
  }
}

bool CastSpell(int index) {
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(index);
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

bool CastSpell(Object *target, int index) {
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(index);
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

bool CastSpell(FLOAT3 pos, int index) {
  if(index < 0 || index > 14) { return false; }
  auto hudInput = *(uintptr_t *)(*(uintptr_t *)oHudInstance + 0x68);
  auto spell = self->GetSpell(index);
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
} // namespace function