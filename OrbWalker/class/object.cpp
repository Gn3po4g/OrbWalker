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

CharacterState Object::state() {
  return prop<CharacterState>(objActionState);
}

ObjectType Object::type() {
  const auto addr = prop<uintptr_t>(objCharacterData);
  if(!IsValidPtr(addr)) return (ObjectType)0;
  const auto data = *(uintptr_t *)(addr + characterDataData);
  return *(ObjectType *)(*(uintptr_t *)(data + characterDataType));
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
  return state() & CharacterState::CanAttack &&
         !HasBuff("KaisaE");
}

bool Object::CanMove() {
  return state() & CharacterState::CanMove;
}

bool Object::HasBuff(std::string_view name) {
  auto &buffManager = *(std::vector<Buff *> *)((uintptr_t)this + objBuffBegin);
  for(auto buff : buffManager) {
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

Object::DataStack *Object::dataStack() {
  return (DataStack *)(uintptr_t(this) + objDataStack);
}

bool Object::CheckSpecialSkins(const char *model, int32_t skin) {
  const auto stack{dataStack()};
  const auto champ_name{fnv::hash_runtime(stack->baseSkin.model.str)};

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

void Object::ChangeSkin(const char *model, int32_t skin) {
  const auto stack{dataStack()};
  ((xor_value<std::int32_t> *)(uintptr_t(this) + objSkinId))->encrypt(skin);
  stack->baseSkin.skin = skin;
  if(!CheckSpecialSkins(model, skin)) {
    stack->update(true);
  }
}

Object *Object::GetOwner() {
  using fnGetOwner = Object *(__fastcall *)(Object *);
  return ((fnGetOwner)(offset::oGetOwner))(this);
}


void Object::DataStack::update(bool change) {
  using fnUpdate = int64_t(__fastcall *)(Object::DataStack *, bool);
  ((fnUpdate)(offset::oDataStackUpdate))(this, change);
}

void Object::DataStack::push(const char *model, int32_t skin) {
  using fnPush = int64_t(__fastcall *)(Object::DataStack *, const char *, int32_t, int32_t, bool, bool, bool, bool, bool, bool, int8_t, const char *, int32_t, const char *, int32_t, bool, int32_t);
  ((fnPush)(offset::oDataStackPush))(this, model, skin, 0, false, false, false, false, true, false, -1, "\x00", 0, "\x00", 0, false, 1);
}

std::span<Object *> ObjList::data() {
  return std::span(prop<Object **>(0x8), prop<int>(0x10));
}

std::set<ObjectType> hashes{ObjectType::Hero, ObjectType::Minion_Lane, ObjectType::Monster, ObjectType::Turret};

Object *ObjList::GetAppropriateObject() {
  auto objList = data() | std::views::filter([](Object *obj) {
                   return obj->IsValidTarget() && hashes.contains(obj->type());
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
  return std::ranges::find(data(), obj) != data().end();
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