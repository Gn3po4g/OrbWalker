#include "stdafx.hpp"

namespace script {
  Object *LocalPlayer() { return *(Object **)offset::oLocalPlayer; }
  ObjList *Heroes() { return *(ObjList **)offset::oHeroList; }
  ObjList *Minions() { return *(ObjList **)offset::oMinionList; }
  ObjList *Turrets() { return *(ObjList **)offset::oTurretList; }

  Object *GetTarget(bool aHero) {
    if(aHero) {
      return Heroes()->GetLowestHealth(false);
    } else {
      if(const auto target = Minions()->GetLowestHealth(true)) {
        return target;
      } else {
        return Turrets()->GetLowestHealth(false);
      }
    }
  }

  void Update() {
    using std::is_gt;
    static float LAT{};
    static float LMT{};
    bool excute{};
    Object *target{};
    if((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) {
      target = GetTarget(true);
      excute = true;
    } else if((GetAsyncKeyState('V') & 0x8000) != 0) {
      target = GetTarget(false);
      excute = true;
    }
    const auto self = LocalPlayer();
    if(!(self && self->IsAlive()) || IsChatOpen() || IsLeagueInBackground() || !excute) return;
    const auto now{GameTime()};
    if(target && is_gt(now <=> LAT + self->AttackDelay() + 15e-3f)) {
      LAT = now;
      last_object = target;
      Attack(target);
    } else if(is_gt(now <=> LMT + 33e-3f) && is_gt(now <=> LAT + self->AttackWindup() + 75e-3f)) {
      LMT = now;
      Move2Mouse();
    }
  }
}// namespace script