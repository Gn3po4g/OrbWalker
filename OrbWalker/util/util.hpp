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

enum GameState : int32_t {
  Loading = 0,
  Connecting = 1,
  Running = 2,
  Paused = 3,
  Finished = 4,
  Exiting = 5
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
  Hero = 7957694998179309635,
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

#pragma pack(push, 4)
template<typename T>
class xor_value {
  bool xor_key_was_init{0};
  std::uint8_t bytes_xor_count;
  std::uint8_t bytes_xor_count_8;
  T xor_key;
  std::uint8_t value_index{0};
  T values_table[4];

public:
  T decrypt() noexcept {
    if(xor_key_was_init != 1)
      return 0;

    auto xored_value{values_table[value_index]};
    auto xor_key_value{xor_key};

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint32_t *>(&xor_key_value)};
      for(auto i{0u}; i < bytes_xor_count; i++)
        *(reinterpret_cast<std::uint32_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
    }

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint8_t *>(&xor_key_value)};

      for(auto i{sizeof(T) - bytes_xor_count_8}; i < sizeof(T); ++i)
        *(reinterpret_cast<std::uint8_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
    }

    return xored_value;
  }

  void encrypt(T value) noexcept {
    if(!xor_key_was_init) {
      if(sizeof(T) <= 2) {
        bytes_xor_count_8 = sizeof(T);
        bytes_xor_count = 0;
      } else {
        bytes_xor_count_8 = sizeof(T) % 4;
        bytes_xor_count = (sizeof(T) - bytes_xor_count_8) / 4;
      }

      auto key{::__rdtsc()};
      auto key_index{0};

      for(auto i{0u}; i < sizeof(T); i++) {
        *(reinterpret_cast<std::uint8_t *>(&xor_key) + i) = *(reinterpret_cast<std::uint8_t *>(&key) + key_index++);

        if(key_index == 8) {
          key = ::__rdtsc();
          key_index = 0;
        }
      }

      value_index = 0;
      xor_key_was_init = 1;
    }

    auto xored_value{value};
    auto xor_key_value{xor_key};

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint32_t *>(&xor_key_value)};
      for(auto i{0u}; i < bytes_xor_count; i++)
        *(reinterpret_cast<std::uint32_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
    }

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint8_t *>(&xor_key_value)};

      for(auto i{sizeof(T) - bytes_xor_count_8}; i < sizeof(T); ++i)
        *(reinterpret_cast<std::uint8_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
    }

    auto new_value_index{std::uint8_t(value_index + 1) & 3};
    values_table[new_value_index] = xored_value;
    value_index = new_value_index;
  }
};
#pragma pack(pop)
