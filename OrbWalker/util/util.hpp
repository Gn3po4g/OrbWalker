enum GameState : int32_t { Loading = 0, Connecting = 1, Running = 2, Paused = 3, Finished = 4, Exiting = 5 };

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

enum CharacterHash : uint32_t {
  SRU_ChaosMinionMelee = 0xB87BB4C7,
  SRU_ChaosMinionRanged = 0xD86EA814,
  SRU_ChaosMinionSiege = 0x6B0C5C0,
  SRU_ChaosMinionSuper = 0x3A6B38CE,
  SRU_OrderMinionMelee = 0xD11193B9,
  SRU_OrderMinionRanged = 0xC44285A2,
  SRU_OrderMinionSiege = 0x1F46A4B2,
  SRU_OrderMinionSuper = 0x530117C0,
  SRU_Plant_Vision = 0x4D61E805,
  SRU_Plant_Satchel = 0xE8814FF5,
  SRU_Plant_Health = 0xC3479CD9,
  SRU_Gromp = 0xD1C19B7E,
  SRU_Krug = 0xA20205E2,
  SRU_KrugMini = 0xF8123C99,
  SRU_KrugMiniMini = 0xA8245C50,
  SRU_Murkwolf = 0x621947DC,
  SRU_MurkwolfMini = 0x9A1D4493,
  SRU_Razorbeak = 0x244E9932,
  SRU_RazorbeakMini = 0xA2C97FE9,
  SRU_Blue = 0xFC505223,
  SRU_Red = 0x9CA35508,
  Sru_Crab = 0x2DB77AF9,
  SRU_Dragon_Air = 0x11D34E07,
  SRU_Dragon_Earth = 0x606DCD87,
  SRU_Dragon_Fire = 0x99A947D9,
  SRU_Dragon_Water = 0x27F996F4,
  SRU_Dragon_Hextech = 0xA076EECE,
  SRU_Dragon_Chemtech = 0xF956A026,
  SRU_Dragon_Elder = 0x5944E907,
  SRU_RiftHerald = 0xDDAF53D2,
  SRU_Baron = 0x68AC12C9,
  HA_ChaosMinionMelee = 0xD1BBDB04,
  HA_ChaosMinionRanged = 0x35751117,
  HA_ChaosMinionSiege = 0x1FF0EBFD,
  HA_ChaosMinionSuper = 0x53AB5F0B,
  HA_OrderMinionMelee = 0xEA51B9F6,
  HA_OrderMinionRanged = 0x2148EEA5,
  HA_OrderMinionSiege = 0x3886CAEF,
  HA_OrderMinionSuper = 0x6C413DFD,
  JammerDevice = 0x8223B6BA,
  SightWard = 0x7C1BCAD9,
  YellowTrinket = 0x40D7E043,
  BlueTrinket = 0xE20532FD,
};

template <typename T>
bool IsValidPtr(T addr) {
  return (uintptr_t)addr > 0x100 && (uintptr_t)addr < 0x7fffffffffff;
}

struct INT2 {
  int x, y;

  ImVec2 ToImVec() const { return ImVec2(static_cast<float>(x), static_cast<float>(y)); }
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

  friend bool operator==(const ByteWithMask &bwm, const uint8_t val) { return !bwm._m || bwm._b == std::byte(val); }

private:
  std::byte _b;
  bool _m;
};

template <typename T>
struct RiotArray {
  uintptr_t unused;
  T *data;
  int32_t size;
  int32_t capacity;
};

struct RiotString8 {
  const char *str;
  int32_t size;
  int32_t capacity;

  std::string get() { return std::string(str, size); }
  operator const char *() { return str; }
};

struct RiotString16 {
  union {
    const char *p_str;
    const char str[16];
  };
  int64_t size;
  int64_t capacity;

  operator std::string() {
    if(size >= 16) return std::string(p_str, size);
    else return std::string(str, size);
  }
};

struct SkinData {
  int32_t skinId;
  int32_t unknown;
  RiotString8 skinName;
};

class IMEMBER {
protected:
  template <typename Type>
  Type MEMBER(uintptr_t offset) {
    return *reinterpret_cast<Type *>(this + offset);
  }

  template <typename Type>
  Type *pMEMBER(uintptr_t offset) {
    return reinterpret_cast<Type *>(this + offset);
  }
};

#pragma pack(push, 4)
template <typename T>
class xor_value {
  bool xor_key_was_init{0};
  std::uint8_t bytes_xor_count;
  std::uint8_t bytes_xor_count_8;
  T xor_key;
  std::uint8_t value_index{0};
  T values_table[4];

public:
  T decrypt() noexcept {
    if(xor_key_was_init != 1) { return 0; }

    auto xored_value{values_table[value_index]};
    auto xor_key_value{xor_key};

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint32_t *>(&xor_key_value)};
      for(auto i{0u}; i < bytes_xor_count; i++) {
        *(reinterpret_cast<std::uint32_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
      }
    }

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint8_t *>(&xor_key_value)};

      for(auto i{sizeof(T) - bytes_xor_count_8}; i < sizeof(T); ++i) {
        *(reinterpret_cast<std::uint8_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
      }
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
      for(auto i{0u}; i < bytes_xor_count; i++) {
        *(reinterpret_cast<std::uint32_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
      }
    }

    {
      auto *xor_value_ptr{reinterpret_cast<std::uint8_t *>(&xor_key_value)};

      for(auto i{sizeof(T) - bytes_xor_count_8}; i < sizeof(T); ++i) {
        *(reinterpret_cast<std::uint8_t *>(&xored_value) + i) ^= ~xor_value_ptr[i];
      }
    }

    auto new_value_index{std::uint8_t(value_index + 1) & 3};
    values_table[new_value_index] = xored_value;
    value_index = new_value_index;
  }
};

#pragma pack(pop)