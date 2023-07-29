#include <dxgi.h>
#include <process.h>
#include "kiero/kiero.h"
import OrbWalker;

HRESULT (WINAPI *oPresent)(IDXGISwapChain *, UINT, UINT);

HRESULT WINAPI HKPresent(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags) {
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

unsigned Start(void*) {
	LoadLibrary("R3nzSkin.dll");
	InitOrb();
	using namespace kiero;
	while (init(RenderType::D3D11) != Status::Success ||
	       bind(8, (void **) &oPresent, (void *) HKPresent) != Status::UnknownError);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	DisableThreadLibraryCalls(hModule);
	if (dwReason == DLL_PROCESS_ATTACH) {
		_beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
	}
	return TRUE;
}