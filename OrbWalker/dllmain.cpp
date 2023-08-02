#include <Windows.h>
#include <dxgi.h>
#include <thread>
#include "orbwalker.hpp"
#include "offset.hpp"
#include "function.hpp"
#include "../Kiero/kiero.h"

bool WINAPI HideThread(const HANDLE hThread) noexcept
{
	__try {
		using FnSetInformationThread = NTSTATUS(NTAPI*)(HANDLE, UINT, PVOID, ULONG);
		const auto NtSetInformationThread = FnSetInformationThread(GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtSetInformationThread"));
		if (!NtSetInformationThread)
			return false;
		if (const auto status{ NtSetInformationThread(hThread, 0x11u, nullptr, 0ul) }; status == 0x00000000)
			return true;
	}
	__except (TRUE) {
		return false;
	}
}

HRESULT(WINAPI* oPresent)(IDXGISwapChain*, UINT, UINT);

HRESULT WINAPI HKPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) Execute(Type::AutoKite);
	else if ((GetAsyncKeyState('V') & 0x8000) != 0) Execute(Type::CleanLane);

	static bool lastState = false;
	static bool currentState = false;
	currentState = GetAsyncKeyState(VK_SPACE) & 0x8000;
	if (currentState) *p_aco = true;
	else if (lastState) *p_aco = false;
	lastState = currentState;

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void Start(void*)
{
	HideThread(GetCurrentThread());
	////LoadLibrary(L"R3nzSkin.dll");
	InitOffset();
	InitFunction();
	InitOrb();
	while (GameTime() < 1.f) std::this_thread::sleep_for(std::chrono::seconds(1));
	PrintMessage("#00FFFF", "Noroby's League of Legends OrbWalker");
	while (
		kiero::init(kiero::RenderType::D3D11) != kiero::Status::Success ||
		kiero::bind(8, (void**)&oPresent, (void*)HKPresent) != kiero::Status::UnknownError
		);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		_beginthread(Start, 0, nullptr);
	}
	return TRUE;
}
