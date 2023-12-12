#pragma once

using i8   = int8_t;
using u8   = uint8_t;
using i16  = int16_t;
using u16  = uint16_t;
using i32  = int32_t;
using u32  = uint32_t;
using i64  = int64_t;
using u64  = uint64_t;
using uptr = uintptr_t;

enum GameState : i32 { Loading, Connecting, Running, Paused, Finished, Exiting };

enum Selector : i32 { HealthLowest, HealthHighest, HealthPercentLowest, DistanceClosest };

enum SpellSlot : i32 {
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
  // SpellSlot_BasicAttack1 = 64,
  // SpellSlot_BasicAttack2 = 65,
};

enum ActionState : u16 {
  CanAttack = 1 << 0,
  CanMove   = 1 << 1,
  CanCast   = 1 << 2,
  Immovable = 1 << 3,
  Unknownz  = 1 << 4,
  IsStealth = 1 << 5,
  Taunted   = 1 << 6,
  Feared    = 1 << 7,
  Fleeing   = 1 << 8,
  Supressed = 1 << 9,
  Asleep    = 1 << 10,
  NearSight = 1 << 11,
  Ghosted   = 1 << 12,
  HasGhost  = 1 << 13,
  Charmed   = 1 << 14,
  NoRender  = 1 << 15
};

enum ObjectType : u64 { Hero = 0xE260302C, Minion = 0xCAA58CB2, Turret = 0xBEBA9102, Inhibitor = 0x60BB49C0 };