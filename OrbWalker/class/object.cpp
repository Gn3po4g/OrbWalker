#include "pch.hpp"

#include "object.hpp"

#include "memory/global.hpp"
#include "memory/offset.hpp"

int32_t Object::index() { return MEMBER<int32_t>(objIndex); }

int32_t Object::team() { return MEMBER<int32_t>(objTeam); }

FLOAT3 Object::position() { return MEMBER<FLOAT3>(objPosition); }

bool Object::visible() { return MEMBER<bool>(objVisible); }

float Object::mana() { return MEMBER<float>(objMana); }

bool Object::targetable() { return MEMBER<bool>(objTargetable); }

float Object::health() { return MEMBER<float>(objHealth); }

float Object::attack_range() { return MEMBER<float>(objAttackRange); }

CharacterState Object::state() { return MEMBER<CharacterState>(objActionState); }

DataStack *Object::dataStack() { return pMEMBER<DataStack>(objDataStack); }

std::vector<Buff *> Object::buffs() { return MEMBER<std::vector<Buff *>>(objBuff); }

std::string Object::name() { return MEMBER<RiotString16>(objName); }

// float Object::attackdamage() {
//   return prop<float>(0x166C) + prop<float>(0x15D8);
// }

float Object::AttackDelay() {
  using fnAttackDelay = float(__fastcall *)(Object *);
  return reinterpret_cast<fnAttackDelay>(oAttackDelay)(this);
}

float Object::AttackWindup() {
  using fnAttackWindup = float(__fastcall *)(Object *, int);
  return reinterpret_cast<fnAttackWindup>(oAttackWindup)(this, 0x40);
}

float Object::BonusRadius() {
  using fnBonusRadius = float(__fastcall *)(Object *);
  // if(IsBuilding()) return 88.4f;
  return (*reinterpret_cast<fnBonusRadius **>(this))[37](this);
}

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall *)(Object *);
  return (*reinterpret_cast<fnIsAlive **>(this))[134](this);
}

bool Object::IsEnemy() { return team() != self->team(); }

bool Object::IsTargetableToTeam() {
  using fnIsTargetableToTeam = bool(__fastcall *)(Object *);
  return reinterpret_cast<fnIsTargetableToTeam>(oIsTargetableToTeam)(this);
}

bool Object::IsValidTarget() { return IsEnemy() && IsTargetableToTeam(); }

bool Object::IsHero() { return std::ranges::count(std::span(heros->data, heros->size), this); }

bool Object::IsBuilding() {
  return std::ranges::count(std::span(turrets->data, turrets->size), this)
      || std::ranges::count(std::span(inhibs->data, inhibs->size), this);
}

bool Object::IsPlant() {
  if(!std::ranges::count(std::span(minions->data, minions->size), this)) return false;
  switch(FNV(dataStack()->baseSkin.model)) {
  case FNVC("SRU_Plant_Health"):
  case FNVC("SRU_Plant_Satchel"):
  case FNVC("SRU_Plant_Vision"):
    return true;
  default:
    return false;
  }
}

bool Object::IsWard() {
  if(!std::ranges::count(std::span(minions->data, minions->size), this)) return false;
  switch(FNV(dataStack()->baseSkin.model)) {
  case FNVC("DominationScout"):
  case FNVC("JammerDevice"):
  case FNVC("SightWard"):
  case FNVC("YellowTrinket"):
  case FNVC("VisionWard"):
  case FNVC("BlueTrinket"):
    return true;
  default:
    return false;
  }
}

float Object::get_mana_cost(size_t index) {
  if(index >= 4) return 0.f;
  return MEMBER<float>(objManaCost + index * 0x18);
}

Spell *Object::GetSpell(uint32_t index) { return pMEMBER<Spell *>(objSpell)[index]; }

Object *Object::GetOwner() {
  using fnGetOwner = Object *(__fastcall *)(Object *);
  return reinterpret_cast<fnGetOwner>(oGetOwner)(this);
}