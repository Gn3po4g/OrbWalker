#include "pch.h"
#include <dxgi.h>

HRESULT (WINAPI*oPresent)(IDXGISwapChain*, UINT, UINT);

HRESULT WINAPI HKPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
  if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) OrbWalker::execute(Type::AutoKite);
  else if ((GetAsyncKeyState('V') & 0x8000) != 0) OrbWalker::execute(Type::CleanLane);
  else if ((GetAsyncKeyState('X') & 0x8000) != 0) OrbWalker::execute(Type::LastHit);

  static bool lastState = false;
  static bool currentState = false;
  currentState = GetAsyncKeyState(VK_SPACE) & 0x8000;
  if (currentState) *(OrbWalker::p_aco) = true;
  else if (lastState) *(OrbWalker::p_aco) = false;
  lastState = currentState;

  return oPresent(pSwapChain, SyncInterval, Flags);
}

void Start(void*) {
  LM_LoadModule(std::string("R3nzSkin.dll").data(), LM_NULL);
  Memory::Initialize();
  Functions::Initialize();
  Renderer::Initialize();
  OrbWalker::Initialize();
  Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends OrbWalker", 0xFFFFFF);
  while (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success ||
    kiero::bind(8, (void**)&oPresent, (void*)HKPresent) != kiero::Status::UnknownError);
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID) {
  if (dwReason == DLL_PROCESS_ATTACH) {
    _beginthread(Start, 0, nullptr);
  }
  return TRUE;
}
