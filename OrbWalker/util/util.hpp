template<typename T>
bool IsValidPtr(T addr) {
  return ((uintptr_t)(addr) > 0x100 && (uintptr_t)(addr) < 0x7fffffffffff /* && !IsBadReadPtr(addr, sizeof(PVOID))*/);
}

struct INT2 {
  int x, y;

  ImVec2 ToImVec() const {
    return ImVec2(static_cast<float>(x), static_cast<float>(y));
  }
};

struct FLOAT3 {
  float x, y, z;

  float operator-(const FLOAT3 &other) {
    const float dx = x - other.x;
    const float dy = y - other.y;
    const float dz = z - other.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
  }
};

struct ByteWithMask {
  ByteWithMask() = default;
  ByteWithMask(int _b, bool _m) : _b(std::byte(_b)), _m(_m) {}

  friend bool operator==(const ByteWithMask &bwm, const uint8_t val) {
    return !bwm._m || bwm._b == std::byte(val);
  }

private:
  std::byte _b;
  bool _m;
};

enum CharacterState : uint16_t {
  CanAttack = 1 << 0,
  CanMove = 1 << 1,
  CanCast = 1 << 2,
  Immovable = 1 << 3,
  Unknownz = 1 << 4,
  IsStealth = 1 << 5,
  Taunted = 1 << 6,
  Feared = 1 << 7,
  Fleeing = 1 << 8,
  Supressed = 1 << 9,
  Asleep = 1 << 10,
  NearSight = 1 << 11,
  Ghosted = 1 << 12,
  HasGhost = 1 << 13,
  Charmed = 1 << 14,
  NoRender = 1 << 15
};

enum ObjectType : uint64_t {
  Champion = 7957694998179309635,
  Ward = 5989923982968774999,
  Minion_Lane = 8944270284747073869,
  Minion_Lane_Siege = 7306920423476651374,
  Minion_Lane_Ranged = 7306930284704785774,
  Minion_Lane_Melee = 7306365152824092014,
  Minion_Lane_Super = 8243118342183806318,
  Monster = 2338042707385937741,
  Monster_Epic = 2340781521963538015,
  Monster_Dragon = 2336927746459059295,
  Special = 2336349411965497427,
  Special_Void = 2340781521963538015,
  Turret = 8247626263119950931,
  UNKNOWN = 5980780305148018688,
  Less = 126939457912832
};

constexpr auto keyMap = std::to_array<std::string_view>(
    {"Tab",
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
     "KeypadEqual"});
