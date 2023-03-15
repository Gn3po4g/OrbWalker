#include "kiero.h"
#include "libmem.h"
#include <dxgi.h>
#include <thread>

HRESULT (WINAPI *oPresent)(IDXGISwapChain *, UINT, UINT) = nullptr;

HRESULT WINAPI HKPresent(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags) {
    if (!Functions::IsChatOpen() && !Functions::IsLeagueInBackground()) {
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) {
            *OrbWalker::pAttackChampionsOnly = true;
            OrbWalker::Execute(Type::AutoKite);
        } else {
            *OrbWalker::pAttackChampionsOnly = false;
            if ((GetAsyncKeyState('V') & 0x8000) != 0) OrbWalker::Execute(Type::CleanLane);
            else if ((GetAsyncKeyState('X') & 0x8000) != 0) OrbWalker::Execute(Type::LastHit);
        }
    }
    return oPresent(pSwapChain, SyncInterval, Flags);
}

unsigned __stdcall Start(void *) {
    LM_LoadModule(std::string("R3nzSkin.dll").data(),LM_NULL);
    Memory::Initialize();
    Functions::Initialize();
    Renderer::Initialize();
    OrbWalker::Initialize();
    Functions::PrintChat(Offsets::oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
    while (kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success ||
           kiero::bind(8, (void **) &oPresent, (void *) HKPresent) != kiero::Status::UnknownError);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        _beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
    }
    return TRUE;
}
