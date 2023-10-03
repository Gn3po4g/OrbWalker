#pragma once

class Offset {
public:
  uintptr_t oGameState, oGameTime, oLocalPlayer, oObjUnderMouse, oHeroList, oTurretList, oMinionList, oChatClient,
    oHudInstance, oViewPort, oChampionManager,

    oPrintChat, oWorldToScreen, oIssueOrder, oIssueMove, oCastSpell, oAttackDelay, oAttackWindup, oIsAlive, oIsTargetableToTeam,
    oBonusRadius, oDataStackUpdate, oDataStackPush, oGetOwner, oTranslateString;

  Offset();
};

extern Offset *offset;