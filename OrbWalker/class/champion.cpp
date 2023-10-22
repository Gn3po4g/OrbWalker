#include "pch.hpp"

#include "champion.hpp"

RiotString8 Champion::championName() { return MEMBER<RiotString8>(0x8); }

std::vector<int32_t> Champion::skins_id() {
  struct SkinData {
    int32_t skin_id;
    int32_t unknown;
    RiotString8 skin_name;
  };
  using std::span, std::ranges::to, std::views::transform;
  const auto [unused, data, size, capacity] = MEMBER<RiotArray<SkinData>>(0xE0);
  return span(data, size) | transform([](const SkinData &skin) { return skin.skin_id; }) | to<std::vector>();
}