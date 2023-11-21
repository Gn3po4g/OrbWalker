#pragma once

#include "offset.hpp"

#include "class/object.hpp"

inline namespace function {
void *swap_chain();

float GameTime();

GameState game_state();

bool IsChatOpen();

bool IsLeagueInBackground();

bool CanSendInput();

template <size_t color, typename... Args>
void PrintMessage(const std::format_string<Args...> fmt, Args &&...args) {
  const auto msg     = std::vformat(fmt.get(), std::make_format_args(args...));
  const auto wrapped = std::format("<font color=#{:0>6x}>{}</font>", color & 0xFFFFFF, msg);
  call_function<void>(RVA(oPrintChat), RVA(oChatClient), wrapped.data(), 4);
}

vec2 WorldToScreen(const vec3 &);

void AttackObject(Object *target);

void Move2Mouse();

void PressKeyAt(WORD, const vec3 &);

void Draw(std::function<void()>);
void Circle(const vec3 &, float, u32, float);
} // namespace function