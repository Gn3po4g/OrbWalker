#pragma once

class Spell : IMEMBER {
public:
  class SpellInput : IMEMBER {
  public:
    void SetCasterHandle(int32_t);
    void SetTargetHandle(int32_t);
    void SetStartPos(FLOAT3);
    void SetEndPos(FLOAT3);
    void SetClickedPos(FLOAT3);
    void SetUnkPos(FLOAT3);
  };
  int16_t level();
  float readyTime();
  SpellInput *spellInput();
  uintptr_t spellInfo();
};

class SpellCast : IMEMBER {
public:
  int32_t type();
  int32_t slot();
  std::string name();

  bool is_attack();
  bool is_attack_reset();
};