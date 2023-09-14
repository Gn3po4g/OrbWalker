#include "stdafx.hpp"

AString Champion::champion_name() {
  return prop<AString>(0x8);
}

std::span<SkinData> Champion::skins() {
  return std::span(prop<SkinData *>(0xE8), prop<int32_t>(0xF0));
}