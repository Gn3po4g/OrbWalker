#pragma once

#include "buff.hpp"
#include "data_stack.hpp"
#include "spell.hpp"

class Object : IMEMBER {
public:
  int32_t index();
  int32_t team();
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

  // float attackdamage();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();

  bool IsAlive();
  bool IsEnemy();
  bool IsTargetableToTeam();
  bool IsValidTarget();
  //bool IsHero();
  //bool IsBuilding();
  //bool IsPlant();
  //bool IsWard();

  bool compare_type_flags(TypeFlag);
  float get_mana_cost(SpellSlot);
  Spell *GetSpell(SpellSlot);
  Object *GetOwner();
};