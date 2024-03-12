#pragma once

class Spell : IMEMBER {
public:
  //class SpellInput : IMEMBER {
  //public:
  //  void SetCasterHandle(int32_t);
  //  void SetTargetHandle(int32_t);
  //  void SetStartPos(FLOAT3);
  //  void SetEndPos(FLOAT3);
  //  void SetClickedPos(FLOAT3);
  //  void SetUnkPos(FLOAT3);
  //};
  i16 level();
  float readyTime();
  //SpellInput *spellInput();
  uptr spell_info();
};

class SpellCast : IMEMBER {
public:
  i32 type();
  i32 slot();
  std::string name();

  bool is_attack();
  bool is_attack_reset();
};