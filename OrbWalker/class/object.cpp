#include "stdafx.hpp"

using namespace offset;

int Object::team() { return prop<int>(objTeam); }

bool Object::visible() { return prop<bool>(objVisible); }

bool Object::targetable() { return prop<bool>(objTargetable); }

CharacterState Object::state() { return prop<CharacterState>(objActionState); }

ObjectType Object::type() {
  const auto addr = prop<uintptr_t>(objCharacterData);
  if(!IsValidPtr(addr)) {
    return (ObjectType)0;
  }
  const auto data = *(uintptr_t*)(addr + characterDataData);
  return *(ObjectType*)(*(uintptr_t*)(data + characterDataType));
}

std::string_view Object::name() { return prop<char*>(objName); }

FLOAT3 Object::position() { return prop<FLOAT3>(objPosition); }

float Object::health() { return prop<float>(objHealth); }

DataStack* Object::dataStack() { return (DataStack*)(uintptr_t(this) + objDataStack); }

//float Object::attackdamage() {
//  return prop<float>(0x166C) + prop<float>(0x15D8);
//}

float Object::AttackDelay() {
  using fnAttackDelay = float(__fastcall*)(Object*);
  return ((fnAttackDelay)oAttackDelay)(this);
}

float Object::AttackWindup() {
  using fnAttackWindup = float(__fastcall*)(Object*, int);
  return ((fnAttackWindup)oAttackWindup)(this, 0x40);
}

float Object::BonusRadius() {
  using fnBonusRadius = float(__fastcall*)(Object*);
  return ((fnBonusRadius)oBonusRadius)(this);
}

float Object::RealAttackRange() { return prop<float>(objAttackRange) + BonusRadius(); }

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall*)(Object*);
  return ((fnIsAlive)oIsAlive)(this);
}

bool Object::IsEnemy() { return team() != script::self->team(); }

bool Object::IsTargetableToTeam() {
  using fnIsTargetableToTeam = bool(__fastcall*)(Object*);
  return ((fnIsTargetableToTeam)offset::oIsTargetableToTeam)(this);
}

bool Object::IsValidTarget() {
  const auto self = script::self;
  return visible() && targetable() && IsEnemy() && IsAlive() && IsTargetableToTeam()
      && position() - self->position() <= self->RealAttackRange() + BonusRadius();
}

bool Object::CanAttack() { return state() & CharacterState::CanAttack && !HasBuff("KaisaE"); }

bool Object::CanMove() { return state() & CharacterState::CanMove; }

bool Object::HasBuff(std::string_view name) {
  auto& buffManager = *(std::vector<Buff*>*)((uintptr_t)this + objBuffBegin);
  for(auto buff : buffManager) {
    if(buff->name() == name && buff->starttime() <= script::gameTime && buff->endtime() >= script::gameTime) {
      return true;
    }
  }
  return false;
}

bool Object::CheckSpecialSkins(const char* model, int32_t skin) {
  const auto stack {dataStack()};
  const auto champ_name {fnv::hash_runtime(stack->baseSkin.model.str)};
  if(champ_name == FNV("Katarina") && (skin >= 29 && skin <= 36)) {
    stack->baseSkin.gear = static_cast<std::int8_t>(0);
  } else if(champ_name == FNV("Renekton") && (skin >= 26 && skin <= 32)) {
    stack->baseSkin.gear = static_cast<std::int8_t>(0);
  } else if(champ_name == FNV("MissFortune") && skin == 16) {
    stack->baseSkin.gear = static_cast<std::int8_t>(0);
  } else if(champ_name == FNV("Lux") || champ_name == FNV("Sona")) {
    if((skin == 7 && champ_name == FNV("Lux")) || (skin == 6 && champ_name == FNV("Sona"))) {
      stack->stack.clear();
      stack->push(model, skin);
      return true;
    } else {
      stack->stack.clear();
    }
  } else if(stack->baseSkin.gear != static_cast<std::int8_t>(-1) && champ_name != FNV("Kayn")) {
    stack->baseSkin.gear = static_cast<std::int8_t>(-1);
  }
  return false;
}

void Object::ChangeSkin(const char* model, int32_t skin) {
  const auto stack {dataStack()};
  ((xor_value<std::int32_t>*)(uintptr_t(this) + objSkinId))->encrypt(skin);
  stack->baseSkin.skin = skin;
  if(!CheckSpecialSkins(model, skin)) {
    stack->update(true);
  }
}

Object* Object::GetOwner() {
  using fnGetOwner = Object*(__fastcall*)(Object*);
  return ((fnGetOwner)(offset::oGetOwner))(this);
}