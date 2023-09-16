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

std::string_view Object::name() { return std::string_view(prop<char*>(objName), prop<int32_t>(objName + 0x8)); }

FLOAT3 Object::position() { return prop<FLOAT3>(objPosition); }

float Object::health() { return prop<float>(objHealth); }

DataStack* Object::dataStack() { return (DataStack*)(uintptr_t(this) + objDataStack); }

//float Object::attackdamage() {
//  return prop<float>(0x166C) + prop<float>(0x15D8);
//}

float Object::AttackDelay() {
  using fnAttackDelay = float(__fastcall*)(Object*);
  auto ad = ((fnAttackDelay)oAttackDelay)(this);
  if(name() == "Graves") {
    ad *= .15f;
  } else if(name() == "Zeri") {
    return 0.f;
  }
  return ad - .09f;
}

float Object::AttackWindup() {
  using fnAttackWindup = float(__fastcall*)(Object*, int);
  return ((fnAttackWindup)oAttackWindup)(this, 0x40) - .03f;
}

float Object::BonusRadius() {
  using fnBonusRadius = float(__fastcall*)(Object*);
  return ((fnBonusRadius)oBonusRadius)(this);
}

float Object::RealAttackRange() {
  if(name() == "Zeri") {
    return prop<float>(objAttackRange) + 200.f + BonusRadius();
  }
  return prop<float>(objAttackRange) + BonusRadius();
}

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
  auto distance = position() - self->position() - BonusRadius();
  if(self->name() == "Zeri") {
    distance += BonusRadius();
  }
  return visible() && targetable() && IsEnemy() && IsAlive() && IsTargetableToTeam()
      && distance <= self->RealAttackRange();
}

bool Object::CanAttack() {
  if(name() == "Kaisa") {
    return (state() & CharacterState::CanAttack) && !HasBuff("KaisaE");
  } else if(name() == "Zeri") {
    return (state() & CharacterState::CanCast) && script::gameTime >= GetSpell(0)->readyTime();
  }
  return state() & CharacterState::CanAttack;
}

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

Spell* Object::GetSpell(int index) { return ((Spell**)((uintptr_t)this + 0x30B8))[index]; }

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