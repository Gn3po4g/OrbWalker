#include "stdafx.hpp"

#include "offset.hpp"

Offset* offset;

using namespace std;

vector<ByteWithMask> pattern2bytes(const string &input) {
  vector<ByteWithMask> result;
  stringstream ss(input);
  for (string s; ss >> s;) {
    try {
      result.emplace_back(stoi(s, nullptr, 16), true);
    } catch (exception e) {
      result.emplace_back();
    }
  }
  return result;
}

uintptr_t FindAddress(const string &pattern) {
  const auto byteArr = pattern2bytes(pattern);
  MODULEINFO moduleInfo{};
  GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));
  const auto begin = (uint8_t *)moduleInfo.lpBaseOfDll;
  const auto size = moduleInfo.SizeOfImage;
  MEMORY_BASIC_INFORMATION mbi{};
  for (auto cur = begin; cur < begin + size; cur += mbi.RegionSize) {
    if (!VirtualQuery(cur, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) {
      continue;
    }
    const auto startAddr = (uint8_t *)mbi.BaseAddress, endAddr = startAddr + mbi.RegionSize;
    const auto result = search(startAddr, endAddr, byteArr.begin(), byteArr.end());
    if (result != endAddr) {
      return (uintptr_t)result;
    }
  }
  return 0;
}

// #define DEBUGMODE

Offset::Offset() {
  struct s_sig{
    uintptr_t &reference;
    string pattern;
    uintptr_t addition;
  };
  auto sigs = std::to_array<s_sig>( {
    {oGameState,          "48 8D 4D D7 48 8B 05 ? ? ? ?",                                         7},
    {oGameTime,           "F3 0F 5C 35 ? ? ? ? 0F 28 F8",                                         4},
    {oLocalPlayer,        "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 48 83 7B ? ?",                 3},
    {oObjUnderMouse,      "48 8B 05 ? ? ? ? 48 8B F9 33 C9 48 8B DA",                             3},
    {oHeroList,           "48 8B 05 ? ? ? ? 45 33 E4 0F 57 C0",                                   3},
    {oTurretList,         "48 8B 1D ? ? ? ? 48 8B 5B 28",                                         3},
    {oMinionList,         "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 45 88",                              3},
    {oChatClient,         "41 FF D1 48 8B 0D ? ? ? ? 0F B6 D8",                                   6},
    {oHudInstance,        "48 8B 0D ? ? ? ? 8B 57 10",                                            3},
    {oViewPort,           "48 8B 3D ? ? ? ? FF 90 ? ? ? ?",                                       3},
    {oChampionManager,    "48 8B 0D ? ? ? ? 48 69 D0 ? ? 00 00 48 8B 05",                         3},

    {oPrintChat,          "E8 ? ? ? ? 4C 8B C3 B2 01",                                            1},
    {oIssueOrder,         "45 33 C0 E8 ? ? ? ? 48 83 C4 48",                                      4},
    {oIssueMove,          "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B F1 41 0F B6 F9", 0},
    {oAttackDelay,        "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?",                                 1},
    {oAttackWindup,       "E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?",                              1},
    {oIsAlive,            "E8 ? ? ? ? 84 C0 74 35 48 8D 8F ? ? ? ?",                              1},
    {oIsTargetableToTeam, "40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 84 C0 74 41",                    0},
    {oBonusRadius,        "E8 ? ? ? ? 0F 28 F8 48 8B D6",                                         1},
    {oWorldToScreen,      "E8 ? ? ? ? 49 8D 97 ? ? ? ? 4C 8D 45 D8",                              1},
    {oDataStackUpdate,    "88 54 24 10 53 55 56 57 41 54 41 55 41 56 41",                         0},
    {oDataStackPush,      "E8 ? ? ? ? 48 8D 8D ? ? 00 00 E8 ? ? ? ? 48 85 C0",                    1},
    {oGetOwner,           "E8 ? ? ? ? 4C 3B F8 0F 94 C0",                                         1},
    {oTranslateString,    "E8 ? ? ? ? BA ? ? ? ? E9 ? ? ? ? 8B 84 24 ? ? ? ?",                    1},
  });
  for (auto &[what, pattern, addition] : sigs) {
    auto address = FindAddress(pattern);
    while (!address) {
#ifdef DEBUGMODE
      MessageBoxA(nullptr, (string("Unable to find ") + pattern).data(), "", MB_OK);
#endif
      this_thread::sleep_for(100ms);
      address = FindAddress(pattern);
    }
    if (!addition) {
      what = address;
    } else {
      address += addition;
      what = address + 4 + *(int32_t *)address;
    }
  }
}