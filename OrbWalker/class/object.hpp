#pragma once

#include "buff.hpp"
#include "data_stack.hpp"
#include "spell.hpp"

class Object : IMEMBER {
public:
  static Object *self();
  static Object *obj_under_mouse();

  u32 team();
  vec3 position();
  bool visible();
  float mana();
  bool targetable();
  float health();
  float max_health();
  float attack_range();
  ActionState state();
  ObjectType type();
  DataStack *dataStack();
  std::vector<Buff *> buffs();
  std::string name();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  void *ops_base();

  bool IsAlive();
  bool IsEnemy();
  bool IsValidTarget();
  bool IsCasting();

  float get_mana_cost(SpellSlot);
  bool has_buff(hash_type);
  Spell *GetSpell(SpellSlot);
  Object *GetOwner();
};