#include "pch.hpp"

void Hook();

BOOL WINAPI HideThread(HANDLE hThread) {
  using fn = NTSTATUS(NTAPI *)(HANDLE, UINT, PVOID, ULONG);
  const auto ntdllModule{GetModuleHandle(TEXT("ntdll.dll"))};
  if (!ntdllModule) return false;
  const auto NtSetInformationThread{(fn)GetProcAddress(ntdllModule, "NtSetInformationThread")};
  if (!NtSetInformationThread) return false;
  return NtSetInformationThread(hThread, 0x11u, nullptr, 0ul) == 0;
}

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
  if (dwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule);
    TCHAR path[2048]{};
    GetModuleFileName((HINSTANCE)&__ImageBase, path, _countof(path));
    // const auto name = std::wstring(path);
    // LoadLibrary(name.substr(name.find_last_of(L'\\') + 1).data());
    LoadLibrary(path);
    std::thread([] {
      if (!HideThread(GetCurrentThread())) return;
      Hook();
    }).detach();
  }
  return TRUE;
}
