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

uint32_t Object::skin_hash() {
  const auto data = MEMBER<uintptr_t>(objCharData);
  if(!IsValidPtr(data)) return 0;
  return *(uint32_t *)(data + 0x18);
}

DataStack *Object::dataStack() { return pMEMBER<DataStack>(objDataStack); }

std::vector<Buff *> Object::buffs() { return MEMBER<std::vector<Buff *>>(objBuff); }

std::string Object::name() {
  return MEMBER<RiotString16>(objName);
}

// float Object::attackdamage() {
//   return prop<float>(0x166C) + prop<float>(0x15D8);
// }

float Object::AttackDelay() {
  using fnAttackDelay = float(__fastcall *)(Object *);
  return ((fnAttackDelay)oAttackDelay)(this);
}

float Object::AttackWindup() {
  using fnAttackWindup = float(__fastcall *)(Object *, int);
  return ((fnAttackWindup)oAttackWindup)(this, 0x40);
}

float Object::BonusRadius() {
  using fnBonusRadius = float(__fastcall *)(Object *);
  auto fn = (*(fnBonusRadius **)this)[37];
  if(is_code_ptr(fn)) { return fn(this); }
  return 0.f;
}

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall *)(Object *);
  auto fn = (*(fnIsAlive **)this)[134];
  if(is_code_ptr(fn)) { return fn(this); }
  return false;
}

bool Object::IsEnemy() { return team() != self->team(); }

bool Object::IsTargetableToTeam() {
  using fnIsTargetableToTeam = bool(__fastcall *)(Object *);
  return ((fnIsTargetableToTeam)oIsTargetableToTeam)(this);
}

bool Object::IsValidTarget() { return visible() && targetable() && IsEnemy() && IsAlive() && IsTargetableToTeam(); }

bool Object::IsHero() { return std::count(heros->data, heros->data + heros->size, this); }

bool Object::IsBuilding() {
  return std::count(turrets->data, turrets->data + turrets->size, this)
      || std::count(inhibs->data, inhibs->data + inhibs->size, this);
}

bool Object::IsPlant() {
  switch(skin_hash()) {
  case CharacterHash::SRU_Plant_Health:
  case CharacterHash::SRU_Plant_Satchel:
  case CharacterHash::SRU_Plant_Vision:
    return true;
  default:
    return false;
  }
}

bool Object::IsWard() {
  switch(skin_hash()) {
  case CharacterHash::JammerDevice:
  case CharacterHash::SightWard:
  case CharacterHash::BlueTrinket:
  case CharacterHash::YellowTrinket:
    return true;
  default:
    return false;
  }
}

float Object::get_mana_cost(int index) {
  if(index < 0 || index > 3) return 0.f;
  return MEMBER<float>(objManaCost + index * 0x18);
}

Spell *Object::GetSpell(uint32_t index) { return pMEMBER<Spell *>(objSpell)[index]; }

bool Object::CheckSpecialSkins(const char *model, int32_t skin) {
  const auto stack{dataStack()};
  const auto champName{FNV(stack->baseSkin.model)};
  if(champName == FNV("Katarina") && (skin >= 29 && skin <= 36)) {
    stack->baseSkin.gear = 0;
  } else if(champName == FNV("Renekton") && (skin >= 26 && skin <= 32)) {
    stack->baseSkin.gear = 0;
  } else if(champName == FNV("MissFortune") && skin == 16) {
    stack->baseSkin.gear = 0;
  } else if(champName == FNV("Lux") || champName == FNV("Sona")) {
    if((skin == 7 && champName == FNV("Lux")) || (skin == 6 && champName == FNV("Sona"))) {
      stack->stack.clear();
      stack->push(model, skin);
      return true;
    } else {
      stack->stack.clear();
    }
  } else if(stack->baseSkin.gear != int8_t(-1) && champName != FNV("Kayn")) {
    stack->baseSkin.gear = int8_t(-1);
  }
  return false;
}

void Object::ChangeSkin(const char *model, int32_t skin) {
  const auto stack{dataStack()};
  pMEMBER<xor_value<int32_t>>(objSkinId)->encrypt(skin);
  stack->baseSkin.skin = skin;
  if(!CheckSpecialSkins(model, skin)) { stack->update(true); }
}

Object *Object::GetOwner() {
  using fnGetOwner = Object *(__fastcall *)(Object *);
  return ((fnGetOwner)oGetOwner)(this);
}