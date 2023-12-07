#include "pch.hpp"

#include "champion.hpp"

RiotString8 Champion::championName() { return MEMBER<RiotString8>(0x8); }

std::vector<i32> Champion::skins_id() {
  using namespace std;
  struct SkinData {
    i32 skin_id;
    i32 unknown;
    RiotString8 skin_name;
  };
  const auto [unused, data, size, capacity] = MEMBER<RiotArray<SkinData>>(0xE0);
  return span(data, size) | views::transform([](const SkinData &skin) { return skin.skin_id; }) | ranges::to<vector>();
}