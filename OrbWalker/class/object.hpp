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

//class Spell : Property {
//public:
//  uintptr_t spellInput();
//  uintptr_t spellInfo();
//};

class Object : Property {
  int team();
  bool visible();
  bool targetable();
  CharacterState actionstate();

public:
  CharacterData *characterdata();
  std::string_view name();
  FLOAT3 position();
  float health();
  float scale();
  //float attackdamage();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  float RealAttackRange();
  bool IsAlive();
  bool IsEnemy();
  bool IsValidTarget();
  bool CanAttack();
  bool CanMove();
  bool HasBuff(std::string_view);
  //Spell *GetSpell(int slotId);
};

class ObjList : Property {
  Object **list();
  int size();

public:
  Object *GetAppropriateObject();
  bool Contains(Object*);
};

class Buff : Property {
public:
  std::string_view name();
  float starttime();
  float endtime();
};