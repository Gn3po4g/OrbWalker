#include "pch.hpp"

#include "agent/hook.hpp"
#include "memory/offset.hpp"

BOOL WINAPI HideThread(HANDLE hThread) {
  using fn = NTSTATUS(NTAPI *)(HANDLE, UINT, PVOID, ULONG);
  const auto ntdllModule{GetModuleHandle(TEXT("ntdll.dll"))};
  if (!ntdllModule) return false;
  const auto NtSetInformationThread{(fn)GetProcAddress(ntdllModule, "NtSetInformationThread")};
  if (!NtSetInformationThread) return false;
  return NtSetInformationThread(hThread, 0x11u, nullptr, 0ul) == 0;
}

void Start() {
  if (!HideThread(GetCurrentThread())) return;
  if (!hook::inst().install()) return;
  std::this_thread::sleep_for(std::chrono::hours::max());
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
  if (dwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    std::thread(Start).detach();
  }
  return TRUE;
}
