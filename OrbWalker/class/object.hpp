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
  bool IsHero();
  bool IsBuilding();
  bool IsPlant();
  bool IsWard();

  float get_mana_cost(size_t);
  Spell *GetSpell(uint32_t);
  Object *GetOwner();
};