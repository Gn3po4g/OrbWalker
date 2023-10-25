#pragma once

class Buff : IMEMBER {
public:
  std::string name();
  float starttime();
  float endtime();
  uint8_t count();
  bool is_valid();
};