#pragma once

#include "class/object.hpp"
#include "class/obj_list.hpp"

bool Init();

inline void *swap_chain{};

inline std::unique_ptr<Object> self;
inline std::unique_ptr<ObjList> heros;
inline std::unique_ptr<ObjList> minions;
inline std::unique_ptr<ObjList> turrets;
inline std::unique_ptr<ObjList> inhibs;
inline std::unique_ptr<Object *> objUnderMouse;

inline void *vmt_in_obj{};

// offsets

const inline uintptr_t base = (uintptr_t)GetModuleHandle(nullptr);

const inline uintptr_t oGameState       = base + 0x21DD2F0; // 48 8D 4D D7 48 8B 05 ? ? ? ?
const inline uintptr_t oGameTime        = base + 0x21E4948; // F3 0F 5C 35 ? ? ? ? 0F 28 F8
const inline uintptr_t oLocalPlayer     = base + 0x21F6AC0; // 48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 48 83 7B ? ?
const inline uintptr_t oObjUnderMouse   = base + 0x21DD4A8; // 48 8B 05 ? ? ? ? 48 8B F9 33 C9 48 8B DA
const inline uintptr_t oHeroList        = base + 0x21DA340; // 48 8B 05 ? ? ? ? 45 33 E4 0F 57 C0
const inline uintptr_t oMinionList      = base + 0x21DD2B0; // 73 0C 48 8B 05 ? ? ? ? F3 0F 10 40 ?
const inline uintptr_t oTurretList      = base + 0x21E3BC0; // 48 8B 1D ? ? ? ? 48 8B 5B 28
const inline uintptr_t oInhibList       = base + 0x21F6DB8; // 48 8B 05 ? ? ? ? 48 89 7C 24 ? 48 8B 58 08
const inline uintptr_t oChatClient      = base + 0x21F6C60; // 41 FF D1 48 8B 0D ? ? ? ? 0F B6 D8
const inline uintptr_t oHudInstance     = base + 0x21DA230; // 48 8B 0D ? ? ? ? 8B 57 10
const inline uintptr_t oViewPort        = base + 0x21DD270; // 48 8B 3D ? ? ? ? FF 90 ? ? ? ?
const inline uintptr_t oChampionManager = base + 0x21DD2E0; // 48 8B 0D ? ? ? ? 48 69 D0 ? ? 00 00 48 8B 05

const inline uintptr_t oPrintChat     = base + 0x85EA50; // E8 ? ? ? ? 4C 8B C3 B2 01
const inline uintptr_t oWorldToScreen = base + 0xE36F00; // E8 ? ? ? ? 49 8D 97 ? ? ? ? 4C 8D 45 D8
const inline uintptr_t oIssueOrder    = base + 0x8BC7E0; // 44 88 44 24 18 48 89 4C 24 08
const inline uintptr_t oIssueMove     = base + 0x8A5D70; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B F1 41
// const inline uintptr_t oCastSpell;        // 48 89 4C 24 ? 55 41 55
const inline uintptr_t oAttackDelay      = base + 0x3A2C90; // E8 ? ? ? ? 33 C0 F3 0F 11 83 ? ? ? ?
const inline uintptr_t oAttackWindup     = base + 0x3A2B90; // E8 ? ? ? ? 48 8B CE F3 0F 11 83 ? ? ? ?
const inline uintptr_t oCompareTypeFlags = base + 0x211E50; // 0F B6 41 48 4C 8B C9
const inline uintptr_t oDataStackUpdate  = base + 0x18A450; // 88 54 24 10 53 55 56 57 41 54 41 55 41 56 41
const inline uintptr_t oDataStackPush    = base + 0x1A0520; // E8 ? ? ? ? 41 8B 97 C8 11 00 00
const inline uintptr_t oGetOwner         = base + 0x204760; // E8 ? ? ? ? 4C 3B F8 0F 94 C0
const inline uintptr_t oTranslateString  = base + 0xD22230; // E8 ? ? ? ? 0F 57 DB 4C 8B C0 F3 0F 5A DE
const inline uintptr_t oMaterialRegistry = base + 0xEA2920; // E8 ? ? ? ? 8B 57 44

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