#include "pch.hpp"

#include "struct.hpp"

RiotString Champion::championName() { return MEMBER<RiotString>(0x8); }

RiotArray<SkinData> Champion::skins() {
  return MEMBER<RiotArray<SkinData>>(0xE0);
}