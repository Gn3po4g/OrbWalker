#include "stdafx.hpp"

namespace script {
  float gameTime{};
  float lastAttackTime{};
  uintptr_t lastSpellCastAddress{};
  enum class OrbState {
    Off,
    Attack,
    Clear
  } orbState;

  Object *GetTarget() {
    if(orbState == OrbState::Attack) {
      return Heroes()->GetLowestHealth(false);
    } else if(orbState == OrbState::Clear) {
      if(const auto target = Minions()->GetLowestHealth(true)) {
        return target;
      } else {
        return Turrets()->GetLowestHealth(false);
      }
    } else {
      return nullptr;
    }
  }

  namespace action {
    float lastActionTime{};

    bool CanDoAction() {
      if(gameTime < lastActionTime + 30e-3f) return false;
      lastActionTime = gameTime;
      return true;
    }

    void Idle() {
      if(LocalPlayer()->CanMove() && CanDoAction()) {
        function::Move2Mouse();
      }
    }

    void Attack() {
      if(auto obj = GetTarget();
         obj &&
         LocalPlayer()->CanAttack() &&
         CanDoAction()) {
        lastObject = obj;
        function::AttackObject(obj);
      } else {
        Idle();
      }
    }

  }// namespace action

  namespace state {
    inline bool IsAttacking() {
      return gameTime < lastAttackTime + LocalPlayer()->AttackWindup() - .03f;
    }

    inline bool IsReloading() {
      return gameTime < lastAttackTime + LocalPlayer()->AttackDelay() - .09f;
    }

    void CheckActiveAttack() {
      auto spellCast = *(uintptr_t *)((uintptr_t)LocalPlayer() + 0x2A20);
      if(spellCast) {
        if((*(int *)(spellCast + 0x10) == -1 ||
            *(int *)(spellCast + 0x124) >= 14) &&
           spellCast != lastSpellCastAddress) {
          lastAttackTime = gameTime;
        }
      }
      lastSpellCastAddress = spellCast;
    }

    void CheckOrbState() {
      if((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) {
        orbState = OrbState::Attack;
      } else if((GetAsyncKeyState('V') & 0x8000) != 0) {
        orbState = OrbState::Clear;
      } else {
        orbState = OrbState::Off;
      }
    }
  }// namespace state

  void Update() {
    gameTime = function::GameTime();
    state::CheckActiveAttack();
    state::CheckOrbState();

    if(!function::CanSendInput() || state::IsAttacking()) return;
    if(orbState != OrbState::Off) {
      if(state::IsReloading()) {
        action::Idle();
      } else {
        action::Attack();
      }
    }
  }
}// namespace script