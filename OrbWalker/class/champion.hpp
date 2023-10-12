#pragma once

class Champion : IMEMBER {
public:
  RiotString8 championName();

  std::vector<int32_t> skins_id();
};