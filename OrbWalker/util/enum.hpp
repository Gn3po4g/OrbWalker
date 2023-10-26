#pragma once

using i8  = int8_t;
using u8  = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
// enum HKey {
//	NO_KEY = 0, ESC, N_1, N_2, N_3, N_4, N_5, N_6, N_7, N_8, N_9, N_0, MINUS, EQUAL, BS, Tab, Q, W, E, R, T, Y, U,
// I, O, P, LBRACKET, RBRACKET, ENTER, CTRL, A, S, D, F, G, 	H, J, K, L, SEMICOLON, SINGLE_QUOTE, TILDE, LSHIFT,
// BACKSLASH, Z, X, C, V, B, N, M, COMMA, DOT, FRONTSLASH, RSHIFT, PRINT_SCREEN, ALT, SPACE,	CAPS, F1, F2, 	F3, F4,
// F5, F6, F7, F8, F9, F10, NUM, SCROLL, HOME, UP, PAGE_UP, NUM_MINUS, LEFT, CENTER, RIGHT, PLUS, END, DOWN, PAGE_DOWN,
// INSERT, DEL
// };

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
  // SpellSlot_BasicAttack1 = 64,
  // SpellSlot_BasicAttack2 = 65,
};

enum CharacterState : uint16_t {
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

enum TypeFlag : int32_t {
  // Object = (1 << 0),         // 0x1
  // NeutralCamp = (1 << 1),    // 0x2
  // DeadObject = (1 << 4),     // 0x10
  // InvalidObject = (1 << 5),  // 0x20
  // AIBaseCommon = (1 << 7),   // 0x80
  // AttackableUnit = (1 << 9), // 0x200
  AI       = 1 << 10, // 0x400
  Minion   = 1 << 11, // 0x800
  Hero     = 1 << 12, // 0x1000
  Turret   = 1 << 13, // 0x2000
  Unknown0 = 1 << 14, // 0x4000
  Missile  = 1 << 15, // 0x8000
  Unknown1 = 1 << 16, // 0x10000
  Building = 1 << 17, // 0x20000
  Unknown2 = 1 << 18, // 0x40000
};