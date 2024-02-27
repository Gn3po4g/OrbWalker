#pragma once

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]

#include "spoof_call.h"

inline uptr RVA(uptr offset) {
  extern uptr base;
  return base + offset;
}

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