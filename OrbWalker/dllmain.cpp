#include <Windows.h>
#include <dxgi.h>
#include <d3d9.h>
#include <thread>
#include "script.hpp"
#include "offset.hpp"
#include "function.hpp"
#include "../Kiero/kiero.h"

bool WINAPI HideThread(const HANDLE hThread) noexcept {
	__try {
		using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE, UINT, PVOID, ULONG);
		const auto module = GetModuleHandle(L"ntdll.dll");
		if (!module) return false;
		const auto proc = GetProcAddress(module, "NtSetInformationThread");
		if (!proc) return false;
		const auto NtSetInformationThread = (FnSetInformationThread)proc;
		if (const auto status = NtSetInformationThread(hThread, 0x11u, nullptr, 0ul); status == 0) return true;
		return false;
	}
	__except (TRUE) {
		return false;
	}
}

HRESULT(WINAPI* oPresent)(IDXGISwapChain*, UINT, UINT);

HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) script::Execute(script::Type::AutoKite);
	else if ((GetAsyncKeyState('V') & 0x8000) != 0) script::Execute(script::Type::CleanLane);

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void Start(void*) {
	HideThread(GetCurrentThread());
	LoadLibrary(L"R3nzSkin.dll");
	offset::Init();
	script::Init();
	while (GameTime() < 1.f) std::this_thread::sleep_for(std::chrono::seconds(1));
	PrintMessage("#00FFFF", "Noroby's League of Legends OrbWalker");
	kiero::init(kiero::RenderType::D3D11);
	kiero::bind(8, (void**)&oPresent, Present);
	while (GameTime() > 0.f) std::this_thread::sleep_for(std::chrono::seconds(1));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		_beginthread(Start, 0, nullptr);
	}
	return TRUE;
}
