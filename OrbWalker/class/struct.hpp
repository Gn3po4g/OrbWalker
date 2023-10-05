#pragma once

template <typename T> struct RiotArray {
  uintptr_t unused;
  T *data;
  int32_t size;
  int32_t capacity;
};

struct RiotString {
  const char *str;
  int32_t size;
  int32_t capacity;

  bool operator==(const char *data) { return !strncmp(str, data, size); }

  std::string operator+(const char *data) { return std::string(str, size) + data; }

  operator const char *() { return str; }
};

struct SkinData {
  int32_t skinId;
  int32_t unknown;
  RiotString skinName;
};

class IMEMBER {
protected:
  template <size_t index, typename ReturnType, typename... Args> ReturnType CallVirtual(Args... args) {
    using Fn = ReturnType(__fastcall *)(uintptr_t, Args...);
    const auto function{(*reinterpret_cast<Fn **>(this))[index]};
    return function((uintptr_t)this, args...);
  }

  template <typename Type> Type MEMBER(uintptr_t offset) { return *reinterpret_cast<Type *>(this + offset); }

  template <typename Type> Type *pMEMBER(uintptr_t offset) { return reinterpret_cast<Type *>(this + offset); }
};

class Buff : IMEMBER {
public:
  std::string_view name();
  float starttime();
  float endtime();
};

class Spell : IMEMBER {
public:
  class SpellInput : IMEMBER {
  public:
    void SetCasterHandle(int32_t);
    void SetTargetHandle(int32_t);
    void SetStartPos(FLOAT3);
    void SetEndPos(FLOAT3);
    void SetClickedPos(FLOAT3);
    void SetUnkPos(FLOAT3);
  };
  int16_t level();
  float readyTime();
  SpellInput *spellInput();
  uintptr_t spellInfo();
};

class Champion : IMEMBER {
public:
  RiotString championName();

  RiotArray<SkinData> skins();
};

class DataStack {
public:
  class Data {
  public:
    RiotString model;
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

class Object : IMEMBER {
public:
  int32_t index();
  int32_t team();
  FLOAT3 position();
  bool visible();
  float mana();
  bool targetable();
  float health();
  CharacterState state();
  DataStack *dataStack();
  uintptr_t spell_cast();
  std::vector<Buff *> buffs();
  std::string_view name();

  // float attackdamage();
  float AttackDelay();
  float AttackWindup();
  float BonusRadius();
  float RealAttackRange();

  bool IsAlive();
  bool IsEnemy();
  bool IsTargetableToTeam();
  bool IsValidTarget();
  bool IsHero();
  bool IsTurret();
  bool IsLaneMinion();
  bool IsJungle();

  float get_mana_cost(int);
  Spell *GetSpell(int);
  bool CheckSpecialSkins(const char *, int32_t);
  void ChangeSkin(const char *, int32_t);
  Object *GetOwner();
};

class ObjList : public RiotArray<Object *> {
public:
  std::vector<Object *> objects_in_range(float, bool);
  Object *best_object_in_range(float, bool);
};

constexpr std::string_view keyMap[] = {
  "Tab",
  "LeftArrow",
  "RightArrow",
  "UpArrow",
  "DownArrow",
  "PageUp",
  "PageDown",
  "Home",
  "End",
  "Insert",
  "Delete",
  "Backspace",
  "Space",
  "Enter",
  "Escape",
  "LeftCtrl",
  "LeftShift",
  "LeftAlt",
  "LeftSuper",
  "RightCtrl",
  "RightShift",
  "RightAlt",
  "RightSuper",
  "Menu",
  "0",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z",
  "F1",
  "F2",
  "F3",
  "F4",
  "F5",
  "F6",
  "F7",
  "F8",
  "F9",
  "F10",
  "F11",
  "F12",
  "'",
  ",",
  "-",
  ".",
  "/",
  ";",
  "=",
  "[",
  "\\",
  "]",
  "`",
  "CapsLock",
  "ScrollLock",
  "NumLock",
  "PrintScreen",
  "Pause",
  "Keypad0",
  "Keypad1",
  "Keypad2",
  "Keypad3",
  "Keypad4",
  "Keypad5",
  "Keypad6",
  "Keypad7",
  "Keypad8",
  "Keypad9",
  "KeypadDecimal",
  "KeypadDivide",
  "KeypadMultiply",
  "KeypadSubtract",
  "KeypadAdd",
  "KeypadEnter",
  "KeypadEqual",
};

static_assert(sizeof(keyMap) / sizeof(decltype(keyMap[0])) == 105);