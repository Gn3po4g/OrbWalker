#pragma once

inline namespace offset {
inline uintptr_t oGameState{}, oGameTime{}, oLocalPlayer{}, oObjUnderMouse{}, oHeroList{}, oMinionList{}, oTurretList{},
  oInhibList{}, oChatClient{}, oHudInstance{}, oViewPort{}, oChampionManager{},

  oPrintChat{}, oWorldToScreen{}, oIssueOrder{}, oIssueMove{}, oCastSpell{}, oAttackDelay{}, oAttackWindup{},
  oIsAlive{}, oIsTargetableToTeam{}, oBonusRadius{}, oCompareTypeFlags, oDataStackUpdate{}, oDataStackPush{},
  oGetOwner{}, oTranslateString{}, oMaterialRegistry{};

void Init();
} // namespace offset