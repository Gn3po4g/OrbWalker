#include "pch.hpp"

#include "object.hpp"

#include "res/offset.hpp"

Object *Object::self() { return Read<Object *>(RVA(oLocalPlayer)); }

Object *Object::obj_under_mouse() { return Read<Object *>(Read<uptr>(RVA(oObjUnderMouse)) + 0x18); }

u32 Object::team() { return MEMBER<u32>(objTeam); }

vec3 Object::position() { return MEMBER<vec3>(objPosition); }

bool Object::visible() { return MEMBER<bool>(objVisible); }

bool Object::targetable() { return MEMBER<bool>(objTargetable) && call_function<bool>(RVA(oTargetableToTeam), this); }

float Object::health() { return MEMBER<float>(objHealth); }

float Object::max_health() { return MEMBER<float>(objMaxHealth); }

float Object::attack_range() { return MEMBER<float>(objAttackRange); }

ActionState Object::state() { return MEMBER<ActionState>(objActionState); }

ObjectType Object::type() { return Read<ObjectType>(call_virtual<1, uptr>(this) + 0x8); }

std::string Object::name() { return MEMBER<std::string>(objName); }

float Object::AttackDelay() { return call_function<float>(RVA(oAttackDelay), this); }

float Object::AttackWindup() { return call_function<float>(RVA(oAttackDelay - 0x100), this, 0x40); }

float Object::BonusRadius() { return call_virtual<37, float>(this); }

void *Object::ops_base() { return pMEMBER<void *>(objOPSBase); }

bool Object::IsAlive() { return call_virtual<138, bool>(this); }

bool Object::IsEnemy() { return team() != self()->team(); }

bool Object::IsValidTarget() {
  const auto flag = visible() && targetable() && IsEnemy() && IsAlive();
  if (type() != Minion || FNV(name()) == FNV("Cherry_Plant_Powerup")) return flag;
  else return flag && max_health() > 6.f;
}

bool Object::IsCasting() { return call_virtual<253, bool>(this); }

bool Object::has_buff(hash_type name) { return call_virtual<58, bool>(this, 0, name); }