#pragma once

template <typename T>
uptr RVA(T addr) {
  return (uptr)GetModuleHandle(nullptr) + (uptr)addr;
}

constexpr uptr oGameState        = 0x21F6F80;
constexpr uptr oGameTime         = 0x21FE6F8;
constexpr uptr oLocalPlayer      = 0x22118D8;
constexpr uptr oObjUnderMouse    = 0x21F7138;
constexpr uptr oHeroList         = 0x21F3FE0;
constexpr uptr oMinionList       = 0x21F6F40;
constexpr uptr oTurretList       = 0x21FD970;
constexpr uptr oInhibList        = 0x2211BB8;
constexpr uptr oChatClient       = 0x2211A60;
constexpr uptr oHudInstance      = 0x21F3ED0;
constexpr uptr oChampionManager  = 0x21F6F70;
constexpr uptr oViewProjMatrix   = 0x225B2C0;

constexpr uptr oPrintChat        = 0x86ACB0;
constexpr uptr oIssueOrder       = 0x8CDE50;
constexpr uptr oIssueMove        = 0x8B6C50;
constexpr uptr oAttackDelay      = 0x3CD100;
constexpr uptr oDataStackUpdate  = 0x18C450;
constexpr uptr oDataStackPush    = 0x1A2790;
constexpr uptr oGetOwner         = 0x206C80;
constexpr uptr oTranslateString  = 0xD35C40;
constexpr uptr oMaterialRegistry = 0xEB7AB0;

constexpr uptr objIndex       = 0x10;
constexpr uptr objPosition    = 0x220;
constexpr uptr objMana        = 0x370;
constexpr uptr objTargetable  = 0xEE0;
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