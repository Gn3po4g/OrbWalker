#include "pch.hpp"

#include "global.hpp"
#include "offset.hpp"

#include "memory/function.hpp"

namespace global {
void Init() {
  swap_chain = Read<void *>(call_function<uintptr_t>(oMaterialRegistry) + 0x1C0);

  self.reset(Read<Object *>(oLocalPlayer));
  heros.reset(Read<ObjList *>(oHeroList));
  minions.reset(Read<ObjList *>(oMinionList));
  turrets.reset(Read<ObjList *>(oTurretList));
  inhibs.reset(Read<ObjList *>(oInhibList));

  objUnderMouse.reset((Object **)(Read<uintptr_t>(oObjUnderMouse) + 0x18));

  vmt_in_obj = (void *)((uintptr_t)self.get() + 0x1198);
}
} // namespace global