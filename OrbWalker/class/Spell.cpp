#include "pch.hpp"

#include "spell.hpp"

// using SpellInput = Spell::SpellInput;

int16_t Spell::level() { return MEMBER<i16>(0x28); }

float Spell::readyTime() { return MEMBER<float>(0x30); }

// SpellInput *Spell::spellInput() { return MEMBER<SpellInput *>(0x128); }
//
// uintptr_t Spell::spellInfo() { return MEMBER<uintptr_t>(0x130); }
//
// void SpellInput::SetCasterHandle(int32_t index) { *pMEMBER<int32_t>(0x10) = index; }
//
// void SpellInput::SetTargetHandle(int32_t index) { *pMEMBER<int32_t>(0x14) = index; }
//
// void SpellInput::SetStartPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x18) = pos; }
//
// void SpellInput::SetEndPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x24) = pos; }
//
// void SpellInput::SetClickedPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x30) = pos; }
//
// void SpellInput::SetUnkPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x3C) = pos; }

int32_t SpellCast::type() { return MEMBER<i32>(0x10); }

int32_t SpellCast::slot() { return MEMBER<i32>(0x11C); }

std::string SpellCast::name() { return Read<RiotString16>(Read<uintptr_t>(this) + 0x28).str(); }

bool SpellCast::is_attack() { return MEMBER<bool>(0x112) || MEMBER<bool>(0x113) || MEMBER<bool>(0x114); }

bool SpellCast::is_attack_reset() {
  static constexpr auto reset_attack_spells = std::to_array<u64>(
    {FNV("ApheliosCrescendumAttack"), FNV("AsheQ"), FNV("DariusNoxianTacticsONH"), FNV("LucianE"), FNV("SivirW"),
     FNV("JaxW"), FNV("VayneTumble")}
  );
  return std::ranges::count(reset_attack_spells, FNV(name()));
}
