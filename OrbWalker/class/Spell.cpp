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

std::string SpellCast::name() { return Read<RiotString16>(Read<uintptr_t>(this) + 0x28).str(); }

bool SpellCast::is_attack() { return MEMBER<bool>(0x112) || MEMBER<bool>(0x113) || MEMBER<bool>(0x114); }

bool SpellCast::is_attack_reset() {
  static constexpr auto reset_attack_spells = std::to_array<hash_type>(
    {FNV("AatroxE"),
     FNV("ApheliosInfernumQ"),
     FNV("AsheQ"),
     FNV("BelvethQDummySpellCast"),
     FNV("BriarQ"),
     FNV("CaitlynWSnare"),
     FNV("CamilleQ"),
     FNV("CamilleQ2"),
     FNV("DariusNoxianTacticsONH"),
     FNV("DrMundoE"),
     FNV("EkkoE"),
     FNV("EliseSpiderW"),
     FNV("FioraE"),
     FNV("FizzW"),
     FNV("GarenQ"),
     FNV("GwenE"),
     FNV("IllaoiW"),
     FNV("JaxW"),
     FNV("KaisaR"),
     FNV("KatarinaE"),
     FNV("KindredQ"),
     FNV("KSanteEAllyDash"),
     FNV("KSanteQ"),
     FNV("KSanteQ3"),
     FNV("LeonaShieldOfDaybreak"),
     FNV("LeonaShieldOfDaybreakAttack"),
     FNV("LucianE"),
     FNV("Meditate"),
     FNV("MonkeyKingDoubleAttack"),
     FNV("NasusQ"),
     FNV("NetherBlade"),
     FNV("NasusQ"),
     FNV("NautilusPiercingGaze"),
     FNV("NetherBlade"),
     FNV("Obduracy"),
     FNV("OlafFrenziedStrikes"),
     FNV("PowerFist"),
     FNV("RellW_MountUp"),
     FNV("RenektonPreExecute"),
     FNV("RengarQ"),
     FNV("RivenTriCleave"),
     FNV("SettQ"),
     FNV("ShyvanaDoubleAttack"),
     FNV("ShyvanaDoubleAttackDragon"),
     FNV("SylasE"),
     FNV("SylasE2"),
     FNV("SylasQ"),
     FNV("SylasR"),
     FNV("SylasW"),
     FNV("Takedown"),
     FNV("TalonQAttack"),
     FNV("TalonQDashAttack"),
     FNV("TrundleTrollSmash"),
     FNV("VayneTumble"),
     FNV("ViegoW"),
     FNV("ViE"),
     FNV("VolibearQ"),
     FNV("VolibearQAttack"),
     FNV("VorpalSpikes"),
     FNV("XinZhaoQ"),
     FNV("YorickQ"),
     FNV("ZacQ"),
     FNV("ZeriE")}
  );
  return std::ranges::contains(reset_attack_spells, FNV(name()));
}
