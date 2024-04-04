#pragma once

#include "spell.hpp"

class Object : IMEMBER {
public:
  static Object *self();
  static Object *obj_under_mouse();

  u32 team();
  vec3 position();
  bool visible();
  bool targetable();
  float health();
  float max_health();
  float attack_range();
  ActionState state();
  ObjectType type();
  std::string name();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  void *ops_base();

  bool IsAlive();
  bool IsEnemy();
  bool IsValidTarget();
  bool IsCasting();

  bool has_buff(hash_type);
};