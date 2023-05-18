#include <dxgi.h>
#include <thread>
#include "../Kiero/kiero.h"
import OrbWalker;

HRESULT(WINAPI* oPresent)(IDXGISwapChain*, UINT, UINT);

HRESULT WINAPI HKPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
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

void Start(void*) {
	//LM_LoadModule(std::string("R3nzSkin.dll").data(), LM_NULL);
	InitOrb();
	using namespace kiero;
	while (init(RenderType::D3D11) != Status::Success || bind(8, (void**)&oPresent, (void*)HKPresent) != Status::UnknownError);
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		_beginthread(Start, 0, nullptr);
	}
	return TRUE;
}