#pragma once

#include "memory/spoof_call.h"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]

template <typename T>
T &Read(auto addr) {
  return *std::bit_cast<T *>(addr);
}

template <typename ReturnType>
ReturnType call_function(uintptr_t func, auto... args) {
  using func_t = ReturnType(__fastcall *)(decltype(args)...);
  return spoof_call((void *)jmp_rbx_0, (func_t)func, std::forward<decltype(args)>(args)...);
}

template <size_t Index, typename ReturnType>
ReturnType call_virtual(void *instance, auto... args) {
  using fn      = ReturnType(__fastcall *)(void *, decltype(args)...);
  auto function = (*std::bit_cast<fn **>(instance))[Index];
  return function(instance, std::forward<decltype(args)>(args)...);
}

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
  Type &MEMBER(auto offset) {
    return *std::bit_cast<Type *>(this + offset);
  }

  template <typename Type>
  Type *pMEMBER(auto offset) {
    return std::bit_cast<Type *>(this + offset);
  }
};

struct screen_pos {
  i32 x, y;

  screen_pos(vec2 v) : x(static_cast<i32>(v.x)), y(static_cast<i32>(v.y)) {}
};

inline float distance(const vec3 &v1, const vec3 &v2) {
  using namespace DirectX;
  const XMVECTOR x1 = XMLoadFloat3(&v1);
  const XMVECTOR x2 = XMLoadFloat3(&v2);
  const XMVECTOR V  = XMVectorSubtract(x2, x1);
  const XMVECTOR X  = XMVector3Length(V);
  return XMVectorGetX(X);
}