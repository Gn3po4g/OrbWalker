#pragma once

#include "memory/spoof_call.h"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]

inline uintptr_t RVA(uintptr_t addr) { return (uintptr_t)GetModuleHandle(nullptr) + addr; }

template <typename T, typename U>
T Read(U addr) {
  return *reinterpret_cast<T *>((uintptr_t)addr);
}

template <typename ReturnType, typename... Args>
ReturnType call_function(uintptr_t func, Args... args) {
  using func_t = ReturnType(__fastcall *)(Args...);
  return spoof_call((void *)jmp_rbx_0, (func_t)func, std::forward<Args>(args)...);
}

template <size_t Index, typename ReturnType, typename... Args>
ReturnType call_virtual(void *instance, Args... args) {
  using fn      = ReturnType(__fastcall *)(void *, Args...);
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
  const char *m_str;
  int32_t m_size;
  int32_t m_capacity;

  std::string str() const { return std::string(m_str, m_size); }
};

struct RiotString16 {
  union {
    const char *p_str;
    const char m_str[16];
  };
  int64_t m_size;
  int64_t m_capacity;

  std::string str() const {
    if (m_size >= 16) return std::string(p_str, m_size);
    else return std::string(m_str, m_size);
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