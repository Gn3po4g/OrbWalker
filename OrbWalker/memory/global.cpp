#include "pch.hpp"

#include "global.hpp"
#include "offset.hpp"

namespace global {
void Init() {
  swap_chain = *(IDXGISwapChain **)(((uintptr_t(__fastcall *)())oMaterialRegistry)() + 0x1C0);

  game_state = (GameState *)(*(uintptr_t *)oGameState + 0xC);
  self = *(Object **)oLocalPlayer;
  heros = *(ObjList **)oHeroList;
  minions = *(ObjList **)oMinionList;
  turrets = *(ObjList **)oTurretList;
  inhibs = *(ObjList **)oInhibList;
  objUnderMouse = (Object **)(*(uintptr_t *)oObjUnderMouse + 0x18);

  vmt_in_obj = (void *)((uintptr_t)self + 0x1198);
}
} // namespace global