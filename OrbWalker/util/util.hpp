#pragma once

#include "memory/spoof_call.h"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]

template <typename T, typename U>
T Read(U addr) {
  return *reinterpret_cast<T *>((uptr)addr);
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

template <typename T>
struct RiotArray {
  uintptr_t unused;
  T *data;
  i32 size;
  i32 capacity;
};

struct RiotString8 {
  const char *m_str;
  i32 m_size;
  i32 m_capacity;

  std::string str() const { return std::string(m_str, m_size); }
};

struct RiotString16 {
  union {
    const char *p_str;
    const char m_str[16];
  };
  i64 m_size;
  i64 m_capacity;

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