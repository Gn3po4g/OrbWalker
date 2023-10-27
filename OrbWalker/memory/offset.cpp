#include "pch.hpp"

#include "offset.hpp"

bool Init() {
  auto game_state = (GameState *)(Read<uintptr_t>(RVA(oGameState)) + 0xC);
  while (*game_state != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  self.reset(Read<Object *>(RVA(oLocalPlayer)));
  if (!self.get()) return false;

  swap_chain = Read<void *>(call_function<uintptr_t>(RVA(oMaterialRegistry)) + 0x1C0);
  heros.reset(Read<ObjList *>(RVA(oHeroList)));
  minions.reset(Read<ObjList *>(RVA(oMinionList)));
  turrets.reset(Read<ObjList *>(RVA(oTurretList)));
  inhibs.reset(Read<ObjList *>(RVA(oInhibList)));
  objUnderMouse.reset((Object **)(Read<uintptr_t>(RVA(oObjUnderMouse)) + 0x18));
  vmt_in_obj = (void *)((uintptr_t)self.get() + 0x1198);
  return true;
}

uintptr_t RVA(uintptr_t addr) { return (uintptr_t)GetModuleHandle(nullptr) + addr; }