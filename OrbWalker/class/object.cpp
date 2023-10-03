#include "pch.hpp"

#include "struct.hpp"

#include "agent/orb.hpp"
#include "memory/offset.hpp"

int32_t Object::index() { return MEMBER<int32_t>(objIndex); }

int32_t Object::team() { return MEMBER<int32_t>(objTeam); }

bool Object::visible() { return MEMBER<bool>(objVisible); }

bool Object::targetable() { return MEMBER<bool>(objTargetable); }

CharacterState Object::state() { return MEMBER<CharacterState>(objActionState); }

ObjectType Object::type() {
  const auto addr = MEMBER<uintptr_t>(objCharacterData);
  if(!IsValidPtr(addr)) { return (ObjectType)0; }
  const auto data = *(uintptr_t *)(addr + characterDataData);
  return *(ObjectType *)(*(uintptr_t *)(data + characterDataType));
}

std::string_view Object::name() { return pMEMBER<const char>(objName); }

FLOAT3 Object::position() { return MEMBER<FLOAT3>(objPosition); }

float Object::health() { return MEMBER<float>(objHealth); }

float Object::mana() { return MEMBER<float>(objMana); }

float Object::mana_cost(int index) {
  if(index < 0 || index > 3) return 0.f;
  return MEMBER<float>(objManaCost + index * 0x18);
}

DataStack *Object::dataStack() { return pMEMBER<DataStack>(objDataStack); }

uintptr_t Object::spell_cast() { return MEMBER<uintptr_t>(0x2A20); }

std::vector<Buff *> Object::buffs() { return MEMBER<std::vector<Buff *>>(objBuff); }

// float Object::attackdamage() {
//   return prop<float>(0x166C) + prop<float>(0x15D8);
// }

float Object::AttackDelay() {
  using fnAttackDelay = float(__fastcall *)(Object *);
  return ((fnAttackDelay)offset->oAttackDelay)(this);
}

float Object::AttackWindup() {
  using fnAttackWindup = float(__fastcall *)(Object *, int);
  return ((fnAttackWindup)offset->oAttackWindup)(this, 0x40);
}

float Object::BonusRadius() {
  using fnBonusRadius = float(__fastcall *)(Object *);
  return ((fnBonusRadius)offset->oBonusRadius)(this);
}

float Object::RealAttackRange() { return MEMBER<float>(objAttackRange) + BonusRadius(); }

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall *)(Object *);
  return ((fnIsAlive)offset->oIsAlive)(this);
}

bool Object::IsEnemy() { return team() != orb->self->team(); }

bool Object::IsTargetableToTeam() {
  using fnIsTargetableToTeam = bool(__fastcall *)(Object *);
  return ((fnIsTargetableToTeam)offset->oIsTargetableToTeam)(this);
}

bool Object::IsValidTarget() { return visible() && targetable() && IsEnemy() && IsAlive() && IsTargetableToTeam(); }

Spell *Object::GetSpell(int index) { return pMEMBER<Spell *>(objSpell)[index]; }

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
  return ((fnGetOwner)(offset->oGetOwner))(this);
}