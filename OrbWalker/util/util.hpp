#pragma once

// template <typename T>
// bool IsValidPtr(T addr) {
//   return (uintptr_t)addr > 0x100 && (uintptr_t)addr < 0x7fffffffffff;
// }

//template <typename T>
//class mem_getter {
//public:
//  mem_getter(uintpr_t base) : m_base(base) {}
//  T operator()() { return *(T *)m_base; }
//  uintptr_t m_base;
//};

template <typename T>
T Read(uintptr_t addr) {
  return *reinterpret_cast<T *>(addr);
}

template <typename ReturnType, typename... Args>
ReturnType call_function(uintptr_t func, Args... args) {
  using func_t = ReturnType(__fastcall *)(Args...);
  return reinterpret_cast<func_t>(func)(std::forward<Args>(args)...);
}

template <size_t Index, typename ReturnType, typename... Args>
ReturnType call_virtual(void *instance, Args... args) {
  using fn = ReturnType(__fastcall *)(void *, Args...);
  auto function = (*static_cast<fn **>(instance))[Index];
  return function(instance, std::forward<Args>(args)...);
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

  std::string get() const { return std::string(str, size); }
  operator const char *() const { return str; }
};

struct RiotString16 {
  union {
    const char *p_str;
    const char str[16];
  };
  int64_t size;
  int64_t capacity;

  operator std::string() const {
    if(size >= 16) return std::string(p_str, size);
    else return std::string(str, size);
  }
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