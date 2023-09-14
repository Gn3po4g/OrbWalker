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
  class CharacterDataStack {
  public:
    class CharacterStackData {
    public:
      AString model;
      char pad0[0x10];
      std::int32_t skin;
      char pad1[0x60];
      std::int8_t gear;
      char pad2[0x7];
    };
    std::vector<CharacterStackData> stack;
    CharacterStackData baseSkin;

    void update(bool);
    void push(const char *, std::int32_t);
  };
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
  CharacterDataStack *characterDataStack();
  bool CheckSpecialSkins(const char *, int32_t);
  void ChangeSkin(const char *, int32_t);
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