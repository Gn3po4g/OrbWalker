#include "pch.hpp"

#include "champion.hpp"

RiotString8 Champion::championName() { return MEMBER<RiotString8>(0x8); }

RiotArray<SkinData> Champion::skins() {
  return MEMBER<RiotArray<SkinData>>(0xE0);
}