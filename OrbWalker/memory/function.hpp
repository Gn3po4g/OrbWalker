#pragma once

#include "class/object.hpp"

inline namespace function {
float GameTime();

bool IsChatOpen();

bool IsLeagueInBackground();

bool CanSendInput();

void PrintMessage(size_t color, std::string_view);

INT2 WorldToScreen(FLOAT3 position);

void AttackObject(Object *target);

void Move2Mouse();

bool CastSpell(uint32_t);
bool CastSpell(Object *, uint32_t);
bool CastSpell(FLOAT3, uint32_t);

void Draw(std::function<void()>);
void Circle(const FLOAT3 &, float, uint32_t, float);
} // namespace function