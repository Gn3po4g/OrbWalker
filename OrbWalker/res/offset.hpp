#pragma once

constexpr uptr oPingNet          = 0x18E3608;
constexpr uptr oGameState        = 0x18F5EB8;
constexpr uptr oGameTime         = 0x18F29F8;
constexpr uptr oLocalPlayer      = 0x19040B0;
constexpr uptr oObjUnderMouse    = 0x18E8E70;
constexpr uptr oMouseScreenPos   = 0x18E8C38;
constexpr uptr oHeroList         = 0x18E3730;
constexpr uptr oMinionList       = 0x18E8C70;
constexpr uptr oTurretList       = 0x18EC0F0;
constexpr uptr oInhibList        = 0x19065C0;
constexpr uptr oChatClient       = 0x1904F40;
constexpr uptr oHudInstance      = 0x18E3628;
constexpr uptr oViewProjMatrix   = 0x1957CD0;
constexpr uptr oGetPing          = 0x5104D0;
constexpr uptr oPrintChat        = 0x8C4F60;
constexpr uptr oIssueOrder       = 0x965B80;
constexpr uptr oIssueMove        = 0x950E60;
constexpr uptr oAttackDelay      = 0x407B80;
constexpr uptr oTargetableToTeam = 0xAFE920;
constexpr uptr oMaterialRegistry = 0xF544C0;

constexpr uptr objIndex       = 0x10;
constexpr uptr objTeam        = 0x3C;
constexpr uptr objPosition    = 0x220;
constexpr uptr objVisible     = 0x348;
constexpr uptr objTargetable  = 0x1018;
constexpr uptr objTargetflag  = 0x1040;
constexpr uptr objHealth      = 0x11E0;
constexpr uptr objMaxHealth   = 0x1208;
constexpr uptr objOPSBase     = 0x13D0;
constexpr uptr objActionState = 0x1620;
constexpr uptr objAttackRange = 0x1974;
constexpr uptr objName        = 0x4400;