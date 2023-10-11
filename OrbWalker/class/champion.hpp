#pragma once

class Champion : IMEMBER {
public:
  RiotString8 championName();

  RiotArray<SkinData> skins();
};