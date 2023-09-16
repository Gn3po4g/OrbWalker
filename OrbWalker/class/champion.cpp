#include "stdafx.hpp"

AString Champion::champion_name() {
  return MEMBER<AString>(0x8);
}

std::span<SkinData> Champion::skins() {
  return std::span(MEMBER<SkinData *>(0xE8), MEMBER<int32_t>(0xF0));
}