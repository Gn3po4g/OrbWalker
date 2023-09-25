#include "pch.hpp"

#include "struct.hpp"

using SpellInput = Spell::SpellInput;

float Spell::readyTime() { return MEMBER<float>(0x30); }

SpellInput* Spell::spellInput() { return MEMBER<SpellInput*>(0x128); }

uintptr_t Spell::spellInfo() { return MEMBER<uintptr_t>(0x130); }

void SpellInput::SetCasterHandle(int32_t index) { *pMEMBER<int32_t>(0x10) = index; }

void SpellInput::SetTargetHandle(int32_t index) { *pMEMBER<int32_t>(0x14) = index; }

void SpellInput::SetStartPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x18) = pos; }

void SpellInput::SetEndPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x24) = pos; }

void SpellInput::SetClickedPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x30) = pos; }

void SpellInput::SetUnkPos(FLOAT3 pos) { *pMEMBER<FLOAT3>(0x3C) = pos; }