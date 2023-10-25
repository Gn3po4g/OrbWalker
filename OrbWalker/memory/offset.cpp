#include "pch.hpp"

#include "offset.hpp"

bool Init() {
  auto game_state = (GameState *)(Read<uintptr_t>(oGameState) + 0xC);
  while (*game_state != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  self.reset(Read<Object *>(oLocalPlayer));
  if (!self.get()) return false;

  swap_chain = Read<void *>(call_function<uintptr_t>(oMaterialRegistry) + 0x1C0);
  heros.reset(Read<ObjList *>(oHeroList));
  minions.reset(Read<ObjList *>(oMinionList));
  turrets.reset(Read<ObjList *>(oTurretList));
  inhibs.reset(Read<ObjList *>(oInhibList));
  objUnderMouse.reset((Object **)(Read<uintptr_t>(oObjUnderMouse) + 0x18));
  vmt_in_obj = (void *)((uintptr_t)self.get() + 0x1198);
  return true;
}
//
//using namespace std;
//
//namespace offset {
//vector<ByteWithMask> pattern2bytes(string_view input) {
//  vector<ByteWithMask> result;
//  stringstream ss(input.data());
//  for (string s; ss >> s;) {
//    try {
//      result.emplace_back(stoi(s, nullptr, 16), true);
//    } catch (...) { result.emplace_back(); }
//  }
//  return result;
//}
//
//uintptr_t FindAddress(string_view pattern) {
//  const auto byteArr = pattern2bytes(pattern);
//  MODULEINFO moduleInfo{};
//  GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &moduleInfo, sizeof(MODULEINFO));
//  const auto begin = (uint8_t *)moduleInfo.lpBaseOfDll;
//  const auto size  = moduleInfo.SizeOfImage;
//  MEMORY_BASIC_INFORMATION mbi{};
//  for (auto cur = begin; cur < begin + size; cur += mbi.RegionSize) {
//    if (!VirtualQuery(cur, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;
//    const auto startAddr = (uint8_t *)mbi.BaseAddress, endAddr = startAddr + mbi.RegionSize;
//    const auto result = search(startAddr, endAddr, byteArr.begin(), byteArr.end());
//    if (result != endAddr) return (uintptr_t)result;
//  }
//  return 0;
//}
//
//struct s_sig {
//  uintptr_t &reference;
//  string pattern;
//  uintptr_t addition;
//};
//
//auto sigs = std::to_array<s_sig>({
//  {oGameState,        "48 8D 4D D7 48 8B 05 ? ? ? ?",                                7},
//  {oLocalPlayer,      "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 48 83 7B ? ?",        3},
//  {oGameTime,         "F3 0F 5C 35 ? ? ? ? 0F 28 F8",                                4},
//  {oObjUnderMouse,    "48 8B 05 ? ? ? ? 48 8B F9 33 C9 48 8B DA",                    3},
//  {oHeroList,         "48 8B 05 ? ? ? ? 45 33 E4 0F 57 C0",                          3},
//  {oMinionList,       "73 0C 48 8B 05 ? ? ? ? F3 0F 10 40 ?",                        5},
//  {oTurretList,       "48 8B 1D ? ? ? ? 48 8B 5B 28",                                3},
//  {oInhibList,        "48 8B 05 ? ? ? ? 48 89 7C 24 ? 48 8B 58 08",                  3},
//  {oChatClient,       "41 FF D1 48 8B 0D ? ? ? ? 0F B6 D8",                          6},
//  {oHudInstance,      "48 8B 0D ? ? ? ? 8B 57 10",                                   3},
//  {oViewPort,         "48 8B 3D ? ? ? ? FF 90 ? ? ? ?",                              3},
//  {oChampionManager,  "48 8B 0D ? ? ? ? 48 69 D0 ? ? 00 00 48 8B 05",                3},
//
//  {oPrintChat,        "E8 ? ? ? ? 4C 8B C3 B2 01",                                   1},
//  {oWorldToScreen,    "E8 ? ? ? ? 49 8D 97 ? ? ? ? 4C 8D 45 D8",                     1},
//  {oIssueOrder,       "44 88 44 24 18 48 89 4C 24 08",                               0},
//  {oIssueMove,        "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B F1 41", 0},
// //{oCastSpell,        "48 89 4C 24 ? 55 41 55",                                               0},
//  {oAttackDelay,      "E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?",                        1},
//  {oAttackWindup,     "E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?",                     1},
//  {oCompareTypeFlags, "0F B6 41 48 4C 8B C9",                                        0},
//  {oDataStackUpdate,  "88 54 24 10 53 55 56 57 41 54 41 55 41 56 41",                0},
//  {oDataStackPush,    "E8 ? ? ? ? 41 8B 97 C8 11 00 00",                             1},
//  {oGetOwner,         "E8 ? ? ? ? 4C 3B F8 0F 94 C0",                                1},
//  {oTranslateString,  "E8 ? ? ? ? 0F 57 DB 4C 8B C0 F3 0F 5A DE",                    1},
//  {oMaterialRegistry, "E8 ? ? ? ? 8B 57 44",                                         1}
//});
//
//void update_offset(s_sig &sig) {
//  auto address{FindAddress(sig.pattern)};
//  while (!address) {
//
//    // MessageBoxA(NULL, ("Unable to find " + sig.pattern).data(), "", MB_OK);
//
//    this_thread::sleep_for(100ms);
//    address = FindAddress(sig.pattern);
//  }
//  if (!sig.addition) {
//    sig.reference = address;
//  } else {
//    address += sig.addition;
//    sig.reference = address + 4 + *(int32_t *)address;
//  }
//}
//
//bool Init() {
//  update_offset(sigs[0]);
//  auto game_state = (GameState *)(Read<uintptr_t>(oGameState) + 0xC);
//  while (*game_state != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
//  update_offset(sigs[1]);
//  if (!Read<Object *>(sigs[1].reference)) return false;
//  for (auto it = sigs.begin() + 2; it != sigs.end(); ++it) { update_offset(*it); }
//  global::Init();
//  return true;
//}
//} // namespace offset

