#include "pch.h"

using namespace std;

Offsets offsets;

namespace Memory
{
  tuple<uintptr_t*, string, uintptr_t> sig_to_scan[] = {
      {&offsets.oGameTime, "F3 0F 5C 35 ? ? ? ? 0F 28 F8", 4}, //ok
      {&offsets.oLocalPlayer, "48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1", 3}, //ok
      {&offsets.oViewProjMatrices, "48 83 EC 28 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 48 83 C4 28", 7}, //ok
      {&offsets.oHeroList, "48 8B 0D ? ? ? ? 48 8D 54 24 ? 33 C0 89 44 24 24", 3}, //ok
      {&offsets.oTurretList, "48 89 0D ? ? ? ? 33 C9", 3}, //ok
      //{ &offsets.oInhibitorList, "A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08", true },
      {&offsets.oMinionList, "48 8B 0D ? ? ? ? E8 ? ? ? ? EB 07", 3}, //ok
      {&offsets.oChatClient, "41 FF D1 48 8B 0D ? ? ? ?", 6}, //ok
      {&offsets.oHudInstance, "48 8B 0D ? ? ? ? 8B 57 10", 3}, //ok

      {&offsets.oPrintChat, "48 8B CB E8 ? ? ? ? E9 ? ? ? ? 48 8D 8F ? ? ? ?", 4}, //ok
      {&offsets.oIssueOrder, "45 33 C0 E8 ? ? ? ? 48 83 C4 48", 4}, //ok
      {&offsets.oGetAttackDelay, "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?", 1}, //ok
      {&offsets.oGetAttackCastDelay, "89 83 ? ? ? ? E8 ? ? ? ? 48 8B CE", 7}, //ok
      {&offsets.oIsAlive, "48 8B D8 E8 ? ? ? ? 84 C0 74 35", 4}, //ok
      {&offsets.oGetRadius, "E8 ? ? ? ? 0F 28 F8 48 8B D3 48 8B CE", 1}
  };

  lm_module_t GameModule{};

  uintptr_t FindAddress(string& pattern) {
    lm_page_t page{};
    page.end = GameModule.base;
    while (page.end < GameModule.end && LM_GetPage(page.end, &page)) {
      if (page.prot & LM_PROT_R) {
        const auto scan_size = page.size - ranges::distance(pattern | views::split(' '));
        if (const auto address = LM_SigScan(pattern.data(), page.base, scan_size);
          address != LM_ADDRESS_BAD) {
          return address;
        }
      }
    }
    return LM_ADDRESS_BAD;
  }

  void Initialize() {
    LM_FindModule(string("League of Legends.exe").data(), &GameModule);
    Scan();
  }

  void Scan() {
    for (auto& [what, pattern, offset] : sig_to_scan) {
      uintptr_t address = FindAddress(pattern);
      while (address == LM_ADDRESS_BAD) {
        //MessageBox(nullptr, (string("unable to find") + pattern).data(), "", MB_OK);
        this_thread::sleep_for(100ms);
        address = FindAddress(pattern);
      }
      *what = address + offset + 4 + *(int32_t*)(address + offset);
    }
  }
}
