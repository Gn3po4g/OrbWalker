#include "stdafx.hpp"

using namespace offset;

int32_t Object::index() { return MEMBER<int32_t>(objIndex); }

int32_t Object::team() { return MEMBER<int32_t>(objTeam); }

bool Object::visible() { return MEMBER<bool>(objVisible); }

bool Object::targetable() { return MEMBER<bool>(objTargetable); }

CharacterState Object::state() { return MEMBER<CharacterState>(objActionState); }

ObjectType Object::type() {
  const auto addr = MEMBER<uintptr_t>(objCharacterData);
  if(!IsValidPtr(addr)) {
    return (ObjectType)0;
  }
  const auto data = *(uintptr_t*)(addr + characterDataData);
  return *(ObjectType*)(*(uintptr_t*)(data + characterDataType));
}

std::string_view Object::name() {
  return std::string_view(MEMBER<char*>(objName), MEMBER<int32_t>(objName + 0x8));
}

FLOAT3 Object::position() { return MEMBER<FLOAT3>(objPosition); }

float Object::health() { return MEMBER<float>(objHealth); }

DataStack* Object::dataStack() { return pMEMBER<DataStack>(objDataStack); }

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
  auto range = MEMBER<float>(objAttackRange) + BonusRadius();
  if(name() == "Zeri") {
    return range += 200.f;
  }
  return range;
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
  auto canAttack = state() & CharacterState::CanAttack;
  if(name() == "Kaisa") {
    return canAttack && !HasBuff("KaisaE");
  } else if(name() == "Zeri") {
    return state() & CharacterState::CanCast && GetSpell(0)->readyTime() <= script::gameTime;
  }
  return canAttack;
}

bool Object::CanMove() { return state() & CharacterState::CanMove; }

bool Object::HasBuff(std::string_view name) {
  auto buffManager = MEMBER<std::vector<Buff*>>(objBuffBegin);
  return std::ranges::any_of(buffManager, [name, time = script::gameTime](Buff* buff) {
    return buff->name() == name && buff->starttime() <= time && buff->endtime() >= time;
  });
}

Spell* Object::GetSpell(int index) { return pMEMBER<Spell*>(objSpell)[index]; }

bool Object::CheckSpecialSkins(const char* model, int32_t skin) {
  const auto stack {dataStack()};
  const auto champName {fnv::hash_runtime(stack->baseSkin.model.str)};
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

void Object::ChangeSkin(const char* model, int32_t skin) {
  const auto stack {dataStack()};
  pMEMBER<xor_value<int32_t>>(objSkinId)->encrypt(skin);
  stack->baseSkin.skin = skin;
  if(!CheckSpecialSkins(model, skin)) {
    stack->update(true);
  }
}

Object* Object::GetOwner() {
  using fnGetOwner = Object*(__fastcall*)(Object*);
  return ((fnGetOwner)(offset::oGetOwner))(this);
}