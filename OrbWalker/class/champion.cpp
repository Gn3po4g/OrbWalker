#include "stdafx.hpp"

AString Champion::champion_name() {
  return prop<AString>(0x8);
}

std::span<Skin> Champion::skins() {
  return std::span(prop<Skin *>(0xE8), prop<int32_t>(0xF0));
}