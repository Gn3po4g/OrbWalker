#include "stdafx.hpp"

std::string_view Buff::name() {
  auto addr = prop<uintptr_t>(0x10);
  if(!addr) {
    return "";
  }
  return (char*)(addr + 0x8);
}

float Buff::starttime() { return prop<float>(0x18); }

float Buff::endtime() { return prop<float>(0x1C); }