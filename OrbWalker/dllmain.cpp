#include "pch.hpp"

#include <Windows.h>

#include "agent/hook.hpp"
#include "memory/offset.hpp"
#include "memory/global.hpp"

bool WINAPI HideThread(HANDLE hThread) noexcept {
  try {
    using fn_set_information_thread = NTSTATUS(NTAPI *)(HANDLE, UINT, PVOID, ULONG);
    const auto module = GetModuleHandle(L"ntdll.dll");
    if(!module) { throw std::exception(); }
    const auto proc = reinterpret_cast<uintptr_t>(GetProcAddress(module, "NtSetInformationThread"));
    if(!proc) { throw std::exception(); }
    const auto nt_set_information_thread = reinterpret_cast<fn_set_information_thread>(proc);
    if(const auto status = nt_set_information_thread(hThread, 0x11u, nullptr, 0ul); status != 0) {
      throw std::exception();
    }
    return true;
  } catch(...) { return false; }
}

void Start() {
  HideThread(GetCurrentThread());
  offset::Init();
  while(*game_state != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  hook = new Hook();
  std::unique_lock lkRun(hook->mRun);
  hook->cvRun.wait(lkRun);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
  if(dwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    //_beginthread(Start, 0, nullptr);
    std::thread(Start).detach();
  }
  return TRUE;
}
