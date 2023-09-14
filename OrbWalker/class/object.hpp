//class Spell : Property {
//public:
//  uintptr_t spellInput();
//  uintptr_t spellInfo();
//};

class Object : Property {
  int team();
  bool visible();
  bool targetable();
  CharacterState state();

public:
  class DataStack {
  public:
    class Data {
    public:
      AString model;
      char pad0[0x10];
      int32_t skin;
      char pad1[0x60];
      int8_t gear;
      char pad2[0x7];
    };
    std::vector<Data> stack;
    Data baseSkin;

    void update(bool);
    void push(const char *, int32_t);
  };
  ObjectType type();
  std::string_view name();
  FLOAT3 position();
  float health();
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
  DataStack *dataStack();
  bool CheckSpecialSkins(const char *, int32_t);
  void ChangeSkin(const char *, int32_t);
  Object* GetOwner();
};

class ObjList : Property {
public:
  std::span<Object *> data();
  Object *GetAppropriateObject();
  bool Contains(Object *);
};

class Buff : Property {
public:
  std::string_view name();
  float starttime();
  float endtime();
};