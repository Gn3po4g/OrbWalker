#pragma once

class SpellCast : IMEMBER {
public:
  i32 type();
  i32 slot();
  std::string name();

  bool is_attack();
  bool is_attack_reset();
};