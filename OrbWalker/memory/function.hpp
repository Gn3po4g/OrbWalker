#pragma once

#include "class/struct.hpp"

namespace function {
float GameTime();

bool IsChatOpen();

bool IsLeagueInBackground();

bool CanSendInput();

void PrintMessage(std::string_view, std::string_view);

INT2 WorldToScreen(FLOAT3 position);

void AttackObject(Object* target);

void Move2Mouse();

bool CastSpell(uint32_t);
bool CastSpell(Object*, uint32_t);
bool CastSpell(FLOAT3, uint32_t);
}  // namespace function