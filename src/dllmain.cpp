#include "pch.h"
#include <process.h>
#include <dxgi.h>
#include <commctrl.h>

using Present_t = HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT);
Present_t OriginPresent = NULL;
bool* aco{};

HRESULT WINAPI HKPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if (!Functions::IsChatOpen() && !Functions::IsLeagueInBackground()) {
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) {
			*aco = 1;
			OrbWalker::AttackChampion();
		} else {
			*aco = 0;
			if ((GetAsyncKeyState('V') & 0x8000) != 0) OrbWalker::CleanLane();
			else if ((GetAsyncKeyState('X') & 0x8000) != 0) OrbWalker::LastHit();
		}
	}
	return OriginPresent(pSwapChain, SyncInterval, Flags);
}

unsigned __stdcall Start(void*) {
	Memory::Initialize();
	Functions::Initialize();
	OrbWalker::Initialize();
	aco = (bool*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x30) + 0x20);
	Functions::PrintChat(offsets.oChatClient, "Noroby's League of Legends Orbwalker", 0xFFFFFF);
	while (
		kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success ||
		kiero::bind(8, (void**)&OriginPresent, HKPresent) != kiero::Status::UnknownError);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		_beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
		CloseHandle(hModule);
	}
	return TRUE;
}
