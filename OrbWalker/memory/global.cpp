#include "pch.hpp"

#include "global.hpp"
#include "offset.hpp"

namespace global {
void Init() {
  game_state = (GameState *)(*(uintptr_t *)oGameState + 0xC);
  self = *(Object **)oLocalPlayer;
  heros = *(ObjList **)oHeroList;
  minions = *(ObjList **)oMinionList;
  turrets = *(ObjList **)oTurretList;
  objUnderMouse = (Object **)(*(uintptr_t *)oObjUnderMouse + 0x18);
}
} // namespace global