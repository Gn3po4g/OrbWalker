#include "pch.hpp"

#include "struct.hpp"

std::string_view Buff::name() {
  auto addr = MEMBER<uintptr_t>(0x10);
  if(!addr) return ""sv;
  return (char *)(addr + 0x8);
}

float Buff::starttime() { return MEMBER<float>(0x18); }

float Buff::endtime() { return MEMBER<float>(0x1C); }