#pragma once

class Buff : IMEMBER {
public:
  std::string name();
  float starttime();
  float endtime();
  uint32_t count();
  bool is_valid();
};