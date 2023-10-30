#pragma once

#include "offset.hpp"

#include "class/object.hpp"

inline namespace function {
float GameTime();

bool IsChatOpen();

bool IsLeagueInBackground();

bool CanSendInput();

template <size_t color, typename... Args>
void PrintMessage(const std::format_string<Args...> fmt, Args &&...args) {
    const auto msg = std::vformat(fmt.get(), std::make_format_args(args...));
    const auto wrapped = std::format("<font color=#{:0>6x}>{}</font>", color & 0xFFFFFF, msg);
    call_function<void>(RVA(oPrintChat), RVA(oChatClient), wrapped.data(), 4);
}

INT2 WorldToScreen(FLOAT3 position);

void AttackObject(Object *target);

void Move2Mouse();

// bool CastSpell(SpellSlot);
// bool CastSpell(Object *, SpellSlot);
// bool CastSpell(FLOAT3, SpellSlot);

void PressKeyAt(WORD, FLOAT3);

void Draw(std::function<void()>);
void Circle(const FLOAT3 &, float, uint32_t, float);
} // namespace function