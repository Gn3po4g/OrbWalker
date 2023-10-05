#pragma once

inline namespace offset {
inline uintptr_t oGameState{}, oGameTime{}, oLocalPlayer{}, oObjUnderMouse{}, oHeroList{}, oMinionList{}, oTurretList{},
  oInhibList{}, oChatClient{}, oHudInstance{}, oViewPort{}, oChampionManager{},

  oPrintChat{}, oWorldToScreen{}, oIssueOrder{}, oIssueMove{}, oCastSpell{}, oAttackDelay{}, oAttackWindup{},
  oIsAlive{}, oIsTargetableToTeam{}, oBonusRadius{}, oDataStackUpdate{}, oDataStackPush{}, oGetOwner{},
  oTranslateString{};

void Init();
} // namespace offset