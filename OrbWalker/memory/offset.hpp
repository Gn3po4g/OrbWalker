#pragma once

#include "class/obj_list.hpp"
#include "class/object.hpp"

bool Init();

uintptr_t RVA(uintptr_t);

bool IsValidPtr(uintptr_t);

inline void *swap_chain{};

inline std::unique_ptr<Object> self;
inline std::unique_ptr<ObjList> heros;
inline std::unique_ptr<ObjList> minions;
inline std::unique_ptr<ObjList> turrets;
inline std::unique_ptr<ObjList> inhibs;
inline std::unique_ptr<Object *> objUnderMouse;

inline void *vmt_in_obj{};

// offsets

constexpr uintptr_t oGameState       = 0x21DD2F0; // 48 8D 4D D7 48 8B 05 ? ? ? ?
constexpr uintptr_t oGameTime        = 0x21E4948; // F3 0F 5C 35 ? ? ? ? 0F 28 F8
constexpr uintptr_t oLocalPlayer     = 0x21F6AC0; // 48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 48 83 7B ? ?
constexpr uintptr_t oObjUnderMouse   = 0x21DD4A8; // 48 8B 05 ? ? ? ? 48 8B F9 33 C9 48 8B DA
constexpr uintptr_t oHeroList        = 0x21DA340; // 48 8B 05 ? ? ? ? 45 33 E4 0F 57 C0
constexpr uintptr_t oMinionList      = 0x21DD2B0; // 73 0C 48 8B 05 ? ? ? ? F3 0F 10 40 ?
constexpr uintptr_t oTurretList      = 0x21E3BC0; // 48 8B 1D ? ? ? ? 48 8B 5B 28
constexpr uintptr_t oInhibList       = 0x21F6DB8; // 48 8B 05 ? ? ? ? 48 89 7C 24 ? 48 8B 58 08
constexpr uintptr_t oChatClient      = 0x21F6C60; // 41 FF D1 48 8B 0D ? ? ? ? 0F B6 D8
constexpr uintptr_t oHudInstance     = 0x21DA230; // 48 8B 0D ? ? ? ? 8B 57 10
constexpr uintptr_t oViewPort        = 0x21DD270; // 48 8B 3D ? ? ? ? FF 90 ? ? ? ?
constexpr uintptr_t oChampionManager = 0x21DD2E0; // 48 8B 0D ? ? ? ? 48 69 D0 ? ? 00 00 48 8B 05

constexpr uintptr_t oPrintChat        = 0x85EAF0; // E8 ? ? ? ? 4C 8B C3 B2 01
constexpr uintptr_t oWorldToScreen    = 0xE36FC0; // E8 ? ? ? ? 49 8D 97 ? ? ? ? 4C 8D 45 D8
constexpr uintptr_t oIssueOrder       = 0x8BC880; // 44 88 44 24 18 48 89 4C 24 08
constexpr uintptr_t oIssueMove        = 0x8A5E10; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B F1 41
constexpr uintptr_t oAttackDelay      = 0x3A2D30; // E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?
constexpr uintptr_t oAttackWindup     = 0x3A2C30; // E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?
constexpr uintptr_t oCompareTypeFlags = 0x211F00; // 0F B6 41 48 4C 8B C9
constexpr uintptr_t oDataStackUpdate  = 0x18A450; // 88 54 24 10 53 55 56 57 41 54 41 55 41 56 41
constexpr uintptr_t oDataStackPush    = 0x1A0520; // E8 ? ? ? ? 41 8B 97 C8 11 00 00
constexpr uintptr_t oGetOwner         = 0x2047D0; // E8 ? ? ? ? 4C 3B F8 0F 94 C0
constexpr uintptr_t oTranslateString  = 0xD222F0; // E8 ? ? ? ? 0F 57 DB 4C 8B C0 F3 0F 5A DE
constexpr uintptr_t oMaterialRegistry = 0xEA29E0; // E8 ? ? ? ? 8B 57 44

constexpr uintptr_t objIndex       = 0x10;
constexpr uintptr_t objTeam        = 0x3C;
constexpr uintptr_t objPosition    = 0x220;
constexpr uintptr_t objVisible     = 0x320;
constexpr uintptr_t objMana        = 0x350;
constexpr uintptr_t objTargetable  = 0xEC0;
constexpr uintptr_t objHealth      = 0x1068;
constexpr uintptr_t objMaxHealth   = 0x1080;
constexpr uintptr_t objSkinId      = 0x1244;
constexpr uintptr_t objActionState = 0x13D0;
constexpr uintptr_t objAttackRange = 0x16C4;
constexpr uintptr_t objBuff        = 0x27D8;
constexpr uintptr_t objManaCost    = 0x2A88;
constexpr uintptr_t objSpell       = 0x30C8;
constexpr uintptr_t objDataStack   = 0x35D0;
constexpr uintptr_t objName        = 0x3868;