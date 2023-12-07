#pragma once

uptr RVA(auto addr) {
  return (uptr)GetModuleHandle(nullptr) + (uptr)addr;
}

constexpr uptr oPingNet          = 0x221C4F0;
//constexpr uptr oGameState        = 0x221DFF0;
constexpr uptr oGameTime         = 0x2226D48;
constexpr uptr oLocalPlayer      = 0x223A0B8;
constexpr uptr oObjUnderMouse    = 0x221F788;
constexpr uptr oMouseScreenPos   = 0x221F558;
constexpr uptr oHeroList         = 0x221C620;
constexpr uptr oMinionList       = 0x221F590;
constexpr uptr oTurretList       = 0x2225FC0;
constexpr uptr oInhibList        = 0x223A3A8;
constexpr uptr oChatClient       = 0x223A250;
constexpr uptr oHudInstance      = 0x221C510;
constexpr uptr oChampionManager  = 0x221F5C0;
constexpr uptr oViewProjMatrix   = 0x2284710;
constexpr uptr oGetPing          = 0x4B1860;
constexpr uptr oPrintChat        = 0x877000;
constexpr uptr oIssueOrder       = 0x8D94A0;
constexpr uptr oIssueMove        = 0x8C2630;
constexpr uptr oAttackDelay      = 0x3D65C0;
constexpr uptr oDataStackUpdate  = 0x18D9F0;
constexpr uptr oDataStackPush    = 0x1A3C50;
constexpr uptr oGetOwner         = 0x208AB0;
constexpr uptr oTranslateString  = 0xD58690;
constexpr uptr oMaterialRegistry = 0xEDD810;


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