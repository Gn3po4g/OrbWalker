#include "stdafx.hpp"

namespace offset {
using namespace std;

uintptr_t oGameTime, oLocalPlayer, oHeroList, oTurretList, oMinionList,
    oChatClient, oHudInstance, oViewPort,

    oPrintChat, oWorldToScreen, oIssueOrder, oIssueMove, oAttackDelay,
    oAttackWindup, oIsAlive, oBonusRadius;

struct {
  uintptr_t &reference;
  string pattern;
  uintptr_t addition;
} sig2scan[] = {{oGameTime, "F3 0F 5C 35 ? ? ? ? 0F 28 F8", 4},
                {oLocalPlayer, "48 8B 05 ? ? ? ? 4C 8B D2 4C 8B C1", 3},
                {oHeroList, "48 8B 05 ? ? ? ? 4C 8B 78 08", 3},
                {oTurretList, "48 8B 1D ? ? ? ? 48 8B 5B 28", 3},
                {oMinionList, "48 89 0D ? ? ? ? 48 8D 05 ? ? ? ? 33 D2", 3},
                {oChatClient, "41 FF D1 48 8B 0D ? ? ? ?", 6},
                {oHudInstance, "48 8B 0D ? ? ? ? 8B 57 10", 3},
                {oViewPort, "48 8B 3D ? ? ? ? FF 90 ? ? ? ?", 3},

                {oPrintChat, "E8 ? ? ? ? 4C 8B C3 B2 01", 1},
                {oWorldToScreen, "48 8B D5 E8 ? ? ? ? 48 83 BF ? ? ? ? ?", 4},
                {oIssueOrder, "45 33 C0 E8 ? ? ? ? 48 83 C4 48", 4},
                {oIssueMove, "44 88 7C 24 ? E8 ? ? ? ? EB 19", 6},
                {oAttackDelay, "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?", 1},
                {oAttackWindup, "89 83 ? ? ? ? E8 ? ? ? ? 48 8B CE", 7},
                {oIsAlive, "E8 ? ? ? ? 84 C0 74 35 48 8D 8F ? ? ? ?", 1},
                {oBonusRadius, "E8 ? ? ? ? 0F 28 F8 48 8B D6", 1}};

vector<ByteWithMask> pattern2bytes(const string &input) {
  using std::byte;
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
  GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr),
                       &moduleInfo, sizeof(MODULEINFO));
  const auto begin = (uint8_t *)moduleInfo.lpBaseOfDll;
  const auto size = moduleInfo.SizeOfImage;
  MEMORY_BASIC_INFORMATION mbi{};
  for (auto cur = begin; cur < begin + size; cur += mbi.RegionSize) {
    if (!VirtualQuery(cur, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT ||
        mbi.Protect == PAGE_NOACCESS) {
      continue;
    }
    const auto startAddr = (uint8_t *)mbi.BaseAddress,
         endAddr = startAddr + mbi.RegionSize;
    const auto result = search(startAddr, endAddr, byteArr.begin(), byteArr.end());
    if (result != endAddr) {
      return (uintptr_t)result;
    }
  }
  return 0;
}

void Init() {
  for (auto &[what, pattern, addition] : sig2scan) {
    auto address = FindAddress(pattern);
    while (!address) {
      // MessageBoxA(nullptr, (string("Unable to find ") + pattern).data(), "",
      // MB_OK);
      this_thread::sleep_for(100ms);
      address = FindAddress(pattern);
    }
    address += addition;
    what = address + 4 + *(int32_t *)address;
  }
}
} // namespace offset