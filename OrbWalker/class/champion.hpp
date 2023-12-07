#pragma once

class Champion : IMEMBER {
public:
  RiotString8 championName();

  std::vector<i32> skins_id();
};