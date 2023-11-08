#pragma once

template <typename T>
uptr RVA(T addr) {
  return (uptr)GetModuleHandle(nullptr) + (uptr)addr;
}

constexpr uptr oGameState       = 0x21F3CC0;
constexpr uptr oLocalPlayer     = 0x220D7D8;
constexpr uptr oGameTime        = 0x21FB3A8;
constexpr uptr oObjUnderMouse   = 0x21F3E78;
constexpr uptr oHeroList        = 0x21F0D20;
constexpr uptr oMinionList      = 0x21F3C80;
constexpr uptr oTurretList      = 0x21FA620;
constexpr uptr oInhibList       = 0x220DAB8;
constexpr uptr oChatClient      = 0x220D960;
constexpr uptr oHudInstance     = 0x21F0C10;
constexpr uptr oViewPort        = 0x21F3C40;
constexpr uptr oChampionManager = 0x21F3CB0;

constexpr uptr oPrintChat        = 0x8633F0;
constexpr uptr oWorldToScreen    = 0xE4B080;
constexpr uptr oIssueOrder       = 0x8C5390;
constexpr uptr oIssueMove        = 0x8AE9A0;
constexpr uptr oAttackDelay      = 0x3A42E0;
constexpr uptr oAttackWindup     = 0x3A41E0;
constexpr uptr oCompareTypeFlags = 0x213030;
constexpr uptr oDataStackUpdate  = 0x18AC80;
constexpr uptr oDataStackPush    = 0x1A0EF0;
constexpr uptr oGetOwner         = 0x2056D0;
constexpr uptr oTranslateString  = 0xD35D70;
constexpr uptr oMaterialRegistry = 0xEB7200;

constexpr uptr objIndex       = 0x10;
constexpr uptr objTeam        = 0x3C;
constexpr uptr objPosition    = 0x220;
constexpr uptr objVisible     = 0x340;
constexpr uptr objMana        = 0x370;
constexpr uptr objTargetable  = 0xEE0;
constexpr uptr objTargetFlags = 0xEF8;
constexpr uptr objHealth      = 0x1088;
constexpr uptr objMaxHealth   = 0x10A0;
constexpr uptr objSkinId      = 0x127C;
constexpr uptr objActionState = 0x1408;
constexpr uptr objAttackRange = 0x16FC;
constexpr uptr objBuff        = 0x2810;
constexpr uptr objManaCost    = 0x2AC8;
constexpr uptr objSpell       = 0x3108;
constexpr uptr objDataStack   = 0x3610;
constexpr uptr objName        = 0x38A8;