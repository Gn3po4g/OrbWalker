#pragma once

class hook {
public:
  static hook &inst();
  bool install();

private:
  hook() = default;
  inline static std::unique_ptr<hook> instance_;
};

class vmt_hook {
public:
  vmt_hook(void *base) : m_base((void ***)base) {
    m_old_vmt = *m_base;
    size_t size{};
    while (m_old_vmt[size] && !IsBadCodePtr((FARPROC)m_old_vmt[size])) { ++size; }
    m_new_vmt = (new void *[size + 1]) + 1;
    std::copy_n(m_old_vmt - 1, size + 1, m_new_vmt - 1);
    *m_base = m_new_vmt;
  }

  ~vmt_hook() {
    *m_base = m_old_vmt;
    delete[] (m_new_vmt - 1);
  }

  template <typename T>
  void hook(size_t idx) {
    m_new_vmt[idx] = (void *)(&T::hooked);
    T::original    = reinterpret_cast<decltype(T::original)>(m_old_vmt[idx]);
  }

private:
  auto hook_function(void *hooked_fn, const size_t index) -> void * {
    m_new_vmt[index] = (void *)(hooked_fn);
    return m_old_vmt[index];
  }

  void ***m_base{};
  void **m_new_vmt{};
  void **m_old_vmt{};
};

//template <typename T>
//class mh_hook {
//public:
//  mh_hook(T target) : m_target(target) {
//    std::call_once(init, [] { MH_Initialize(); });
//  }
//  ~mh_hook() { MH_DisableHook(m_target); }
//  template <typename U>
//  void hook() {
//    MH_CreateHook(m_target, U::hooked, reinterpret_cast<LPVOID *>(&U::original));
//    MH_EnableHook(m_target);
//  }
//
//private:
//  T m_target{};
//  inline static std::once_flag init;
//};