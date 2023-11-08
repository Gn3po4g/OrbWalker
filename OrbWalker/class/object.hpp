#pragma once

#include "buff.hpp"
#include "data_stack.hpp"
#include "spell.hpp"

class Object : IMEMBER {
public:
  static Object *self();
  static Object *obj_under_mouse();

  i32 index();
  i32 team();
  FLOAT3 position();
  bool visible();
  float mana();
  bool targetable();
  float health();
  float max_health();
  float attack_range();
  CharacterState state();
  DataStack *dataStack();
  std::vector<Buff *> buffs();
  std::string name();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  void *ops_base();

  bool IsAlive();
  bool IsEnemy();
  bool IsTargetableToTeam();
  bool IsValidTarget();

  bool compare_type_flags(TypeFlag);
  float get_mana_cost(SpellSlot);
  Spell *GetSpell(SpellSlot);
  Object *GetOwner();
};