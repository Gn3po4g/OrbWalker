#include "pch.h"
#pragma comment(lib, "detours.lib")

using EndSceneProto = HRESULT(WINAPI *)(LPDIRECT3DDEVICE9);
EndSceneProto OriginEndScene;

HRESULT WINAPI HookedEndScene(const LPDIRECT3DDEVICE9 pDevice) {
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) orbWalker->AttackObject(true);
	else if ((GetAsyncKeyState('V') & 0x8000) != 0) orbWalker->AttackObject(false);
	return OriginEndScene(pDevice);
}

DWORD WINAPI Start(LPVOID) noexcept {
	do {
		Sleep(500);
		Scan();
	} while (GetGameTime() < 500);
	functions = std::make_unique<Functions>();
	orbWalker = std::make_unique<OrbWalker>();
	OriginEndScene = reinterpret_cast<EndSceneProto>(GetDeviceAddress(42));
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)OriginEndScene, HookedEndScene);
	DetourTransactionCommit();
	return 0;
}

BOOL APIENTRY DllMain(const HMODULE hModule, const DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(nullptr, 0, Start, nullptr, 0, nullptr);
		CloseHandle(hModule);
		return TRUE;
	}
	return FALSE;
}
