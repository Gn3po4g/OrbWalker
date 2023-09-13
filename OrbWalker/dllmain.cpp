#include "stdafx.hpp"

bool WINAPI HideThread(HANDLE hThread) noexcept {
  __try {
    using FnSetInformationThread = NTSTATUS(NTAPI *)(HANDLE, UINT, PVOID, ULONG);
    const auto module = GetModuleHandle(L"ntdll.dll");
    if(!module) return false;
    const auto proc = GetProcAddress(module, "NtSetInformationThread");
    if(!proc) return false;
    const auto NtSetInformationThread = (FnSetInformationThread)proc;
    if(const auto status = NtSetInformationThread(hThread, 0x11u, nullptr, 0ul); status == 0) return true;
    return false;
  } __except(TRUE) {
    return false;
  }
}

void Start(void *) {
  HideThread(GetCurrentThread());
  LoadLibrary(L"R3nzSkin.dll");
  offset::Init();
  while(function::GameTime() < .5f) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  hooks::Init();
  while(hooks::running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
  if(dwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    _beginthread(Start, 0, nullptr);
  }
  return TRUE;
}
