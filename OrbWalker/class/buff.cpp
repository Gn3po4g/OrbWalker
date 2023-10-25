#include "pch.hpp"

#include "buff.hpp"

std::string Buff::name() { return *(const char **)(MEMBER<uintptr_t>(0x10) + 0x8); }

float Buff::starttime() { return MEMBER<float>(0x18); }

float Buff::endtime() { return MEMBER<float>(0x1C); }

uint8_t Buff::count() { return MEMBER<uint8_t>(0x38); }

bool Buff::is_valid() { return count() && MEMBER<uintptr_t>(0x10) || MEMBER<uint8_t>(0x88); }
