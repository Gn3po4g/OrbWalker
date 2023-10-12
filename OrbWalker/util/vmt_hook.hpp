#include "Windows.h"

inline auto is_code_ptr(void *ptr) -> bool {
  auto flags{PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY};

  MEMORY_BASIC_INFORMATION out;
  VirtualQuery(ptr, &out, sizeof(out));

  return out.Type && !(out.Protect & (PAGE_GUARD | PAGE_NOACCESS)) && out.Protect & flags;
}

class vmt_hook {
public:
  vmt_hook(void *base) : m_base((void ***)base) {
    m_old_vmt = *m_base;
    size_t size{};
    while(m_old_vmt[size] && is_code_ptr(m_old_vmt[size])) { ++size; }
    m_new_vmt = (new void *[size + 1]) + 1;
    std::copy_n(m_old_vmt - 1, size + 1, m_new_vmt - 1);
    *m_base = m_new_vmt;
  }

  ~vmt_hook() {
    *m_base = m_old_vmt;
    delete[](m_new_vmt - 1);
  }

  template <typename T>
  void hook(size_t idx) {
    // T::original = (T::original)hook_function(&T::hooked, idx);
    m_new_vmt[idx] = (void *)(&T::hooked);
    T::original = decltype(T::original)(m_old_vmt[idx]);
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