#include "pch.hpp"

#include "object.hpp"

#include "memory/global.hpp"
#include "memory/offset.hpp"
#include "memory/function.hpp"

int32_t Object::index() { return MEMBER<int32_t>(objIndex); }

int32_t Object::team() { return MEMBER<int32_t>(objTeam); }

FLOAT3 Object::position() { return MEMBER<FLOAT3>(objPosition); }

bool Object::visible() { return MEMBER<bool>(objVisible); }

float Object::mana() { return MEMBER<float>(objMana); }

bool Object::targetable() { return MEMBER<bool>(objTargetable); }

float Object::health() { return MEMBER<float>(objHealth); }

float Object::max_health() { return MEMBER<float>(objMaxHealth); }

float Object::attack_range() { return MEMBER<float>(objAttackRange); }

CharacterState Object::state() { return MEMBER<CharacterState>(objActionState); }

DataStack *Object::dataStack() {
  if (!compare_type_flags(AI)) return nullptr;
  return pMEMBER<DataStack>(objDataStack);
}

std::vector<Buff *> Object::buffs() {
  if (!compare_type_flags(AI)) return {};
  return MEMBER<std::vector<Buff *>>(objBuff);
}

std::string Object::name() { return MEMBER<RiotString16>(objName).str(); }

// float Object::attackdamage() {
//   return prop<float>(0x166C) + prop<float>(0x15D8);
// }

float Object::AttackDelay() { return call_function<float>(oAttackDelay, this); }

float Object::AttackWindup() { return call_function<float>(oAttackWindup, this, 65); }

float Object::BonusRadius() { return call_virtual<37, float>(this); }

bool Object::IsAlive() { return call_virtual<134, bool>(this); }

bool Object::IsEnemy() { return team() != self->team(); }

bool Object::IsTargetableToTeam() {
  auto flags = MEMBER<int32_t>(0xED8);
  return flags == 4 || flags == 1;
}

bool Object::IsValidTarget() { return IsEnemy() && IsAlive() && visible() && targetable() && IsTargetableToTeam(); }

bool Object::compare_type_flags(TypeFlag flag) { return call_function<bool>(oCompareTypeFlags, this, flag); }

float Object::get_mana_cost(SpellSlot slot) {
  if (slot > SpellSlot_R) return 0.f;
  return MEMBER<float>(objManaCost + slot * 0x18ull);
}

Spell *Object::GetSpell(SpellSlot slot) { return pMEMBER<Spell *>(objSpell)[slot]; }

Object *Object::GetOwner() { return call_function<Object *>(oGetOwner, this); }