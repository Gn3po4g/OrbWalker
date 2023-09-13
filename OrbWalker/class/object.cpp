#include "stdafx.hpp"

using namespace offset;

int Object::team() {
  return prop<int>(objTeam);
}

bool Object::visible() {
  return prop<bool>(objVisible);
}

bool Object::targetable() {
  return prop<bool>(objTargetable);
}

CharacterState Object::actionstate() {
  return prop<CharacterState>(objActionState);
}

CharacterData *Object::characterdata() {
  const auto addr = prop<uintptr_t>(objCharacterData);
  if(!IsValidPtr(addr)) return nullptr;
  return *(CharacterData **)(addr + characterDataData);
}

std::string_view Object::name() {
  return prop<char *>(objName);
}

FLOAT3 Object::position() {
  return prop<FLOAT3>(objPosition);
}

float Object::health() {
  return prop<float>(objHealth);
}

float Object::scale() {
  return prop<float>(objScale);
}

//float Object::attackdamage() {
//  return prop<float>(0x166C) + prop<float>(0x15D8);
//}

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
  return ((fnBonusRadius)oBonusRadius)(this);
}

float Object::RealAttackRange() {
  return prop<float>(objAttackRange) + BonusRadius();
}

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall *)(Object *);
  return ((fnIsAlive)oIsAlive)(this);
}

bool Object::IsEnemy() {
  return team() != script::self->team();
}

bool Object::IsValidTarget() {
  const auto self = script::self;
  return IsEnemy() && visible() && targetable() && IsAlive() &&
         position() - self->position() <= self->RealAttackRange() + BonusRadius();
}

bool Object::CanAttack() {
  return actionstate() & CharacterState::CanAttack &&
         !HasBuff("KaisaE");
}

bool Object::CanMove() {
  return actionstate() & CharacterState::CanMove;
}

bool Object::HasBuff(std::string_view name) {
  auto begin = prop<Buff **>(objBuffBegin);
  auto end = prop<Buff **>(objBuffEnd);
  if(!IsValidPtr(begin) || !IsValidPtr(end)) return false;
  for(auto buff : std::span(begin, end)) {
    if(buff->name() == name &&
       buff->starttime() <= script::gameTime &&
       buff->endtime() >= script::gameTime) {
      return true;
    }
  }
  return false;
}

//Spell *Object::GetSpell(int slotId) {
//  return ((Spell **)((uintptr_t)this + 0x29E8 + 0x6D0))[slotId];
//}

Object **ObjList::list() {
  return prop<Object **>(0x8);
}

int ObjList::size() {
  return prop<int>(0x10);
}

std::set<ObjectType> hashes{ObjectType::Champion, ObjectType::Minion_Lane, ObjectType::Monster, ObjectType::Turret};

Object *ObjList::GetAppropriateObject() {
  auto objList = std::span(list(), size()) | std::views::filter([](Object *obj) {
                   return obj->IsValidTarget() && hashes.contains(obj->characterdata()->type());
                 });
  auto target = std::ranges::min_element(objList, {}, [self = script::self](Object *obj) {
    using config::Targeting;
    if(config::targeting == (int)Targeting::health_lowest) {
      return obj->health();
    } else if(config::targeting == (int)Targeting::distance_closest) {
      return obj->position() - self->position();
    } else {
      return obj->health();
    }
  });
  if(target == objList.end()) {
    return nullptr;
  } else {
    return *target;
  }
}

bool ObjList::Contains(Object *obj) {
  for(auto o : std::span(list(), size())) {
    if(obj == o) {
      return true;
    }
  }
  return false;
}

float CharacterData::size() {
  return prop<float>(characterDataSize);
}

ObjectType CharacterData::type() {
  return *(ObjectType *)(prop<uintptr_t>(characterDataType));
}

//uintptr_t Spell::spellInput() {
//  return prop<uintptr_t>(0x108);
//}
//
//uintptr_t Spell::spellInfo() {
//  return prop<uintptr_t>(0x130);
//}

std::string_view Buff::name() {
  auto addr = prop<uintptr_t>(0x10);
  if(!addr) return "";
  return (char *)(addr + 0x8);
}

float Buff::starttime() {
  return prop<float>(0x18);
}

float Buff::endtime() {
  return prop<float>(0x1C);
}