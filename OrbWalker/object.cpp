#include "stdafx.hpp"

using namespace offset;

float CharacterData::size() {
  return prop<float>(0xC4);
}

ObjectType CharacterData::type() {
  return *(ObjectType *)(prop<uintptr_t>(0x770));
}

std::string Buff::name() {
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

int Object::team() {
  return prop<int>(0x3C);
}

bool Object::visible() {
  return prop<bool>(0x310);
}

bool Object::targetable() {
  return prop<bool>(0xEB0);
}

CharacterState Object::actionstate() {
  return prop<CharacterState>(0x13C0);
}

CharacterData *Object::characterdata() {
  return *(CharacterData **)(prop<uintptr_t>(0x3528) + 0x28);
}

FLOAT3 Object::position() {
  return prop<FLOAT3>(0x220);
}

float Object::health() {
  return prop<float>(0x1058);
}

float Object::scale() {
  return prop<float>(0x1684);
}

float Object::attackdamage() {
  return prop<float>(0x15D8) + prop<float>(0x1670);
}

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
  return prop<float>(0x16B4) + BonusRadius();
}

bool Object::IsAlive() {
  using fnIsAlive = bool(__fastcall *)(Object *);
  return ((fnIsAlive)oIsAlive)(this);
}

bool Object::IsValidTarget() {
  auto self = script::LocalPlayer();
  return team() != self->team() && visible() && targetable() && IsAlive() &&
         position() - self->position() <= self->RealAttackRange() + BonusRadius();
}

bool Object::CanAttack() {
  return actionstate() & CharacterState::CanAttack &&
         !HasBuff("KaisaE");
}

bool Object::CanMove() {
  return actionstate() & CharacterState::CanMove;
}

bool Object::HasBuff(std::string name) {
  auto begin = prop<Buff **>(0x27C8);
  auto end = prop<Buff **>(0x27D0);
  for(auto buff : std::span(begin, end)) {
    if(buff->name() == name &&
       buff->starttime() <= script::gameTime &&
       buff->endtime() >= script::gameTime) {
      return true;
    }
  }
  return false;
}

Object **ObjList::list() {
  return prop<Object **>(0x8);
}

int ObjList::size() {
  return prop<int>(0x10);
}

Object *lastObject{};
std::set<ObjectType> hashes{ObjectType::Champion, ObjectType::Minion_Lane, ObjectType::Monster, ObjectType::Turret};

Object *ObjList::GetLowestHealth(bool dif) {
  auto objList = std::span(list(), size()) | std::views::filter([](Object *obj) {
                   return obj->IsValidTarget() && hashes.contains(obj->characterdata()->type());
                 });
  auto target = std::ranges::min_element(objList, {}, [self = script::LocalPlayer(), dif](Object *obj) {
    if(dif && obj->health() > self->attackdamage() && obj == lastObject) {
      return FLT_MAX;
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
