class Property {
protected:
  template<typename Type>
  inline Type prop(uintptr_t offset) {
    return *reinterpret_cast<Type *>(reinterpret_cast<uintptr_t>(this) + offset);
  }
};

class CharacterData : Property {
public:
  float size();
  ObjectType type();
  //int64_t GetObjectTypeHashDetailed();
};

class Buff : Property {
public:
  std::string name();
  float starttime();
  float endtime();
};

class Object : Property {
  int team();
  bool visible();
  bool targetable();
  CharacterState actionstate();

public:
  CharacterData *characterdata();
  FLOAT3 position();
  float health();
  float scale();
  float attackdamage();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  float RealAttackRange();
  bool IsAlive();
  bool IsValidTarget();
  bool CanAttack();
  bool CanMove();
  bool HasBuff(std::string);
};

extern Object *lastObject;

class ObjList : Property {
  Object **list();
  int size();

public:
  Object *GetLowestHealth(bool);
};
