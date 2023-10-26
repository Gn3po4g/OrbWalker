#include "pch.hpp"

#include "buff.hpp"

#include "memory/offset.hpp"

std::string Buff::name() {
  const auto addr = MEMBER<uintptr_t>(0x10) + 0x8;
  const auto size = MEMBER<uintptr_t>(0x10) + 0x8 + 0x8;
  if (IsBadReadPtr((void *)size, sizeof(i32) || IsBadReadPtr((void *)addr, Read<i32>(size)))) { return ""; }
  return *(const char **)addr;
}

float Buff::starttime() { return MEMBER<float>(0x18); }

float Buff::endtime() { return MEMBER<float>(0x1C); }

uint32_t Buff::count() { return MEMBER<uint32_t>(0x8C); }

bool Buff::is_valid() { return MEMBER<uint8_t>(0x38) && MEMBER<uintptr_t>(0x10) || MEMBER<uint8_t>(0x88); }
