#pragma once

#include "class/obj_list.hpp"
#include "class/object.hpp"

bool Init();

uptr RVA(uptr);

inline void *swap_chain{};

inline std::unique_ptr<Object> self;
inline std::unique_ptr<ObjList> heros;
inline std::unique_ptr<ObjList> minions;
inline std::unique_ptr<ObjList> turrets;
inline std::unique_ptr<ObjList> inhibs;
inline std::unique_ptr<Object *> objUnderMouse;

inline void *vmt_in_obj{};

// offsets

constexpr uptr oGameState       = 0x21DD2F0;
constexpr uptr oGameTime        = 0x21E4948;
constexpr uptr oLocalPlayer     = 0x21F6AC0;
constexpr uptr oObjUnderMouse   = 0x21DD4A8;
constexpr uptr oHeroList        = 0x21DA340;
constexpr uptr oMinionList      = 0x21DD2B0;
constexpr uptr oTurretList      = 0x21E3BC0;
constexpr uptr oInhibList       = 0x21F6DB8;
constexpr uptr oChatClient      = 0x21F6C60;
constexpr uptr oHudInstance     = 0x21DA230;
constexpr uptr oViewPort        = 0x21DD270;
constexpr uptr oChampionManager = 0x21DD2E0;

constexpr uptr oPrintChat        = 0x85EAF0;
constexpr uptr oWorldToScreen    = 0xE36FC0;
constexpr uptr oIssueOrder       = 0x8BC880;
constexpr uptr oIssueMove        = 0x8A5E10;
constexpr uptr oAttackDelay      = 0x3A2D30;
constexpr uptr oAttackWindup     = 0x3A2C30;
constexpr uptr oCompareTypeFlags = 0x211F00;
constexpr uptr oDataStackUpdate  = 0x18A450;
constexpr uptr oDataStackPush    = 0x1A0520;
constexpr uptr oGetOwner         = 0x2047D0;
constexpr uptr oTranslateString  = 0xD222F0;
constexpr uptr oMaterialRegistry = 0xEA29E0;

constexpr uptr objIndex       = 0x10;
constexpr uptr objTeam        = 0x3C;
constexpr uptr objPosition    = 0x220;
constexpr uptr objVisible     = 0x320;
constexpr uptr objMana        = 0x350;
constexpr uptr objTargetable  = 0xEC0;
constexpr uptr objHealth      = 0x1068;
constexpr uptr objMaxHealth   = 0x1080;
constexpr uptr objSkinId      = 0x1244;
constexpr uptr objActionState = 0x13D0;
constexpr uptr objAttackRange = 0x16C4;
constexpr uptr objBuff        = 0x27D8;
constexpr uptr objManaCost    = 0x2A90;
constexpr uptr objSpell       = 0x30D0;
constexpr uptr objDataStack   = 0x35D0;
constexpr uptr objName        = 0x3868;