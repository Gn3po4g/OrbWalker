#include "pch.hpp"

#include "spell.hpp"

i16 Spell::level() { return MEMBER<i16>(0x28); }

float Spell::readyTime() { return MEMBER<float>(0x30); }

// SpellInput *Spell::spellInput() { return MEMBER<SpellInput *>(0x128); }
//
uptr Spell::spell_info() { return MEMBER<uptr>(0x130); }
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

i32 SpellCast::type() { return MEMBER<i32>(0x10); }

i32 SpellCast::slot() { return MEMBER<i32>(0x11C); }

std::string SpellCast::name() {
  return Read<std::string>(Read<uptr>(this) + 0x28);
}

bool SpellCast::is_attack() { return MEMBER<bool>(0x12a) || MEMBER<bool>(0x12b) || MEMBER<bool>(0x12c); }

hash_type reset_attack_spells[]{
  "AatroxE"_FNV,
  "ApheliosInfernumQ"_FNV,
  "AsheQ"_FNV,
  "BelvethQDummySpellCast"_FNV,
  "BriarQ"_FNV,
  "CaitlynWSnare"_FNV,
  "CamilleQ"_FNV,
  "CamilleQ2"_FNV,
  "DariusNoxianTacticsONH"_FNV,
  "DrMundoE"_FNV,
  "EkkoE"_FNV,
  "EliseSpiderW"_FNV,
  "FioraE"_FNV,
  "FizzW"_FNV,
  "GarenQ"_FNV,
  "GwenE"_FNV,
  "IllaoiW"_FNV,
  "JaxW"_FNV,
  "KaisaR"_FNV,
  "KatarinaE"_FNV,
  "KindredQ"_FNV,
  "KSanteEAllyDash"_FNV,
  "KSanteQ"_FNV,
  "KSanteQ3"_FNV,
  "LeonaShieldOfDaybreak"_FNV,
  "LeonaShieldOfDaybreakAttack"_FNV,
  "LucianE"_FNV,
  "Meditate"_FNV,
  "MonkeyKingDoubleAttack"_FNV,
  "NasusQ"_FNV,
  "NetherBlade"_FNV,
  "NasusQ"_FNV,
  "NautilusPiercingGaze"_FNV,
  "NetherBlade"_FNV,
  "Obduracy"_FNV,
  "OlafFrenziedStrikes"_FNV,
  "PowerFist"_FNV,
  "RellW_MountUp"_FNV,
  "RenektonPreExecute"_FNV,
  "RengarQ"_FNV,
  "RivenTriCleave"_FNV,
  "SettQ"_FNV,
  "ShyvanaDoubleAttack"_FNV,
  "ShyvanaDoubleAttackDragon"_FNV,
  "SylasE"_FNV,
  "SylasE2"_FNV,
  "SylasQ"_FNV,
  "SylasR"_FNV,
  "SylasW"_FNV,
  "Takedown"_FNV,
  "TalonQAttack"_FNV,
  "TalonQDashAttack"_FNV,
  "TrundleTrollSmash"_FNV,
  "VayneTumble"_FNV,
  "ViegoW"_FNV,
  "ViE"_FNV,
  "VolibearQ"_FNV,
  "VolibearQAttack"_FNV,
  "VorpalSpikes"_FNV,
  "XinZhaoQ"_FNV,
  "YorickQ"_FNV,
  "ZacQ"_FNV,
};

bool SpellCast::is_attack_reset() { return std::ranges::contains(reset_attack_spells, FNV(name())); }
