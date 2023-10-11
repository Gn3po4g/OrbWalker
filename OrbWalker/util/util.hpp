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