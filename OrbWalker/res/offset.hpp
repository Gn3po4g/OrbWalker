#pragma once

constexpr uptr oPingNet          = 0x224C650;
constexpr uptr oGameState        = 0x224FB40;
constexpr uptr oGameTime         = 0x2257158;
constexpr uptr oLocalPlayer      = 0x226B000;
constexpr uptr oObjUnderMouse    = 0x224FD10;
constexpr uptr oMouseScreenPos   = 0x224FAC8;
constexpr uptr oHeroList         = 0x224C788;
constexpr uptr oMinionList       = 0x224FB00;
constexpr uptr oTurretList       = 0x22563D0;
constexpr uptr oInhibList        = 0x226B310;
constexpr uptr oChatClient       = 0x226B168;
constexpr uptr oHudInstance      = 0x224C670;
constexpr uptr oViewProjMatrix   = 0x22B7010;
constexpr uptr oGetPing          = 0x4C55C0;
constexpr uptr oPrintChat        = 0x890D20;
constexpr uptr oIssueOrder       = 0x8F8820;
constexpr uptr oIssueMove        = 0x8E0ED0;
constexpr uptr oAttackDelay      = 0x3C6920;
constexpr uptr oTargetableToTeam = 0xA84390;
constexpr uptr oMaterialRegistry = 0xF074D0;

constexpr uptr objIndex       = 0x10;
constexpr uptr objPosition    = 0x220;
constexpr uptr objVisible     = 0x348;
constexpr uptr objMana        = 0x378;
constexpr uptr objTargetable  = 0xEE8;
constexpr uptr objTargetflag  = 0xF00;
constexpr uptr objHealth      = 0x1090;
constexpr uptr objMaxHealth   = 0x10A8;
constexpr uptr objActionState = 0x1410;
constexpr uptr objAttackRange = 0x1704;
constexpr uptr objBuff        = 0x2818;
constexpr uptr objManaCost    = 0x2AE8;
constexpr uptr objSpell       = 0x3128;
constexpr uptr objName        = 0x38C8;