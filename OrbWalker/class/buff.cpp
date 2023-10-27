#include "pch.hpp"

#include "buff.hpp"

#include "memory/offset.hpp"

std::string Buff::name() {
  const auto name = MEMBER<RiotArray<const char> *>(0x10);
  return std::string(name->data, name->size);
}

float Buff::starttime() { return MEMBER<float>(0x18); }

float Buff::endtime() { return MEMBER<float>(0x1C); }

uint32_t Buff::count() { return MEMBER<u32>(0x8C); }

bool Buff::is_valid() { return MEMBER<u8>(0x38) && MEMBER<uintptr_t>(0x10) || MEMBER<u8>(0x88); }
