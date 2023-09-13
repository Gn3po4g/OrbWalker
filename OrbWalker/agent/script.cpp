#include "stdafx.hpp"

namespace script {
  float gameTime{};
  Object *markedObject{};
  Object *self{};
  ObjList *heros{};
  ObjList *minions{};
  ObjList *turrets{};

  float lastAttackTime{};
  uintptr_t lastSpellCastAddress{};
  enum class OrbState {
    Off,
    Kite,
    Clear
  } orbState;


  namespace action {
    float lastActionTime{};

    void CheckMarkedObject() {
      if(ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
        auto obj = *(Object **)(*(uintptr_t *)(offset::oObjUnderMouse) + 0x18);
        if(heros->Contains(obj) && obj->IsEnemy()) {
          markedObject = obj;
        } else {
          markedObject = nullptr;
        }
      }
    }

    Object *GetTarget() {
      if(orbState == OrbState::Kite) {
        if(markedObject && markedObject->IsValidTarget()) {
          return markedObject;
        } else {
          return heros->GetAppropriateObject();
        }
      } else if(orbState == OrbState::Clear) {
        if(const auto target = minions->GetAppropriateObject()) {
          return target;
        } else {
          return turrets->GetAppropriateObject();
        }
      } else {
        return nullptr;
      }
    }

    bool CanDoAction() {
      if(gameTime < lastActionTime + .03f) return false;
      lastActionTime = gameTime;
      return true;
    }

    void Idle() {
      if(self->CanMove() && CanDoAction()) {
        function::Move2Mouse();
      }
    }

    //void CastSpell(int spellId, Object *target) {
    //  typedef bool(__fastcall * fnCastSpellWrapper)(uintptr_t hudSpellInfo, uintptr_t spellInfo);
    //  fnCastSpellWrapper _fnCastSpellWrapper = (fnCastSpellWrapper)((uintptr_t)GetModuleHandle(nullptr) + 0x8AF600);

    //  if(spellId < 0 || spellId >= 14) return;
    //  const auto spell = LocalPlayer()->GetSpell(spellId);
    //  const auto spellInfo = spell->spellInfo();
    //  const auto spellInput = spell->spellInput();

    //  *reinterpret_cast<FLOAT3 *>(spellInput + 0x18) = LocalPlayer()->position();
    //  *reinterpret_cast<float *>(spellInput + 0x24) = target->position().x;
    //  *reinterpret_cast<float *>(spellInput + 0x24 + 4) = target->position().y;
    //  *reinterpret_cast<float *>(spellInput + 0x24 + 8) = target->position().z;

    //  _fnCastSpellWrapper(*(uintptr_t *)(*(uintptr_t *)offset::oHudInstance + 0x68), spellInfo);
    //}


    void Attack() {
      const auto obj = GetTarget();
      if(obj && self->CanAttack() && CanDoAction()) {
        function::AttackObject(obj);
        //if(LocalPlayer()->name() == "Zeri") {
        //  CastSpell(0, obj);
        //} else {
        //  function::AttackObject(obj);
        //}
      } else {
        Idle();
      }
    }

  }// namespace action

  namespace state {
    inline bool IsAttacking() {
      return gameTime < lastAttackTime + self->AttackWindup() - .03f;
    }

    inline bool IsReloading() {
      return gameTime < lastAttackTime + self->AttackDelay() - .09f;
    }

    void CheckActiveAttack() {
      auto spellCast = *(uintptr_t *)((uintptr_t)self + 0x2A20);
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
      if(ImGui::IsKeyDown(config::kiteKey)) {
        orbState = OrbState::Kite;
      } else if(ImGui::IsKeyDown(config::cleanKey)) {
        orbState = OrbState::Clear;
      } else {
        orbState = OrbState::Off;
      }
    }
  }// namespace state

  void Init() {
    self = *(Object **)offset::oLocalPlayer;
    heros = *(ObjList **)offset::oHeroList;
    minions = *(ObjList **)offset::oMinionList;
    turrets = *(ObjList **)offset::oTurretList;
  }

  void Update() {
    gameTime = function::GameTime();
    state::CheckActiveAttack();
    state::CheckOrbState();
    action::CheckMarkedObject();

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