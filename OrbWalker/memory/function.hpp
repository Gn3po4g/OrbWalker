#pragma once

#include "offset.hpp"

#include "class/object.hpp"

inline namespace function {
void *swap_chain();

float GameTime();

float ping();

GameState game_state();

vec2 WorldToScreen(const vec3 &);

void AttackObject(Object *target);

void Move2Mouse();

void PressKeyAt(SpellSlot, const vec3 &);

void Draw(std::function<void()>);

void Circle(const vec3 &, float, u32, float);
} // namespace function