#include "stdafx.hpp"

using SpellInput = Spell::SpellInput;

float Spell::readyTime() { return MEMBER<float>(0x30); }

SpellInput* Spell::spellInput() { return MEMBER<SpellInput*>(0x128); }

uintptr_t Spell::spellInfo() { return MEMBER<uintptr_t>(0x130); }

void SpellInput::SetCasterHandle(int index) { *reinterpret_cast<uintptr_t*>(this + 0x10) = index; }

void SpellInput::SetTargetHandle(int index) { *reinterpret_cast<uintptr_t*>(this + 0x14) = index; }

void SpellInput::SetStartPos(FLOAT3 pos) { *reinterpret_cast<FLOAT3*>(this + 0x18) = pos; }

void SpellInput::SetEndPos(FLOAT3 pos) { *reinterpret_cast<FLOAT3*>(this + 0x24) = pos; }

void SpellInput::SetClickedPos(FLOAT3 pos) { *reinterpret_cast<FLOAT3*>(this + 0x24 + sizeof(FLOAT3)) = pos; }

void SpellInput::SetUnkPos(FLOAT3 pos) { *reinterpret_cast<FLOAT3*>(this + 0x24 + sizeof(FLOAT3) * 2) = pos; }