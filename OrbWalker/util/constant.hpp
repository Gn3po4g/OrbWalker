#pragma once

constexpr auto objIndex = 0x10;
constexpr auto objTeam = 0x3C;
constexpr auto objPosition = 0x220;
constexpr auto objVisible = 0x320;
constexpr auto objMana = 0x350;
constexpr auto objTargetable = 0xEC0;
constexpr auto objHealth = 0x1068;
constexpr auto objSkinId = 0x1244;
constexpr auto objActionState = 0x13D0;
constexpr auto objAttackRange = 0x16C4;
constexpr auto objBuff = 0x27D8;
constexpr auto objManaCost = 0x2A88;
constexpr auto objSpell = 0x30C8;
constexpr auto objDataStack = 0x35D0;
constexpr auto objName = 0x3868;

enum GameState : int32_t { Loading, Connecting, Running, Paused, Finished, Exiting };

enum SpellSlot : int32_t {
  SpellSlot_Q,
  SpellSlot_W,
  SpellSlot_E,
  SpellSlot_R,
  SpellSlot_Summoner1,
  SpellSlot_Summoner2,
  SpellSlot_Item1,
  SpellSlot_Item2,
  SpellSlot_Item3,
  SpellSlot_Item4,
  SpellSlot_Item5,
  SpellSlot_Item6,
  SpellSlot_Trinket,
  SpellSlot_Recall,
  SpellSlot_Other,
  // SpellSlot_SpecialAttack = 45,
  //SpellSlot_BasicAttack1 = 64,
  //SpellSlot_BasicAttack2 = 65,
};

enum CharacterState : uint16_t {
  CanAttack = 1 << 0,
  CanMove = 1 << 1,
  CanCast = 1 << 2,
  Immovable = 1 << 3,
  Unknownz = 1 << 4,
  IsStealth = 1 << 5,
  Taunted = 1 << 6,
  Feared = 1 << 7,
  Fleeing = 1 << 8,
  Supressed = 1 << 9,
  Asleep = 1 << 10,
  NearSight = 1 << 11,
  Ghosted = 1 << 12,
  HasGhost = 1 << 13,
  Charmed = 1 << 14,
  NoRender = 1 << 15
};