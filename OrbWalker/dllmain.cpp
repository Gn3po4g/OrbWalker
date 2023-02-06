#include "pch.h"

std::unique_ptr<Memory> m;
std::unique_ptr<Functions> f;
std::unique_ptr<OrbWalker> o;

void CALLBACK TimerProc(HWND, UINT, UINT, DWORD) {
	if(*(bool*)(*(PDWORD)(offsets.oChatClient) + 0x6BC)) return;
	if((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) o->AttackObject(true);
	else if((GetAsyncKeyState('V') & 0x8000) != 0) o->AttackObject(false);
}

DWORD WINAPI Start(LPVOID) {
	m = std::make_unique<Memory>();
	f = std::make_unique<Functions>();
	o = std::make_unique<OrbWalker>();
	const auto tId = SetTimer(nullptr, 1, 20, TimerProc);
	MSG msg;
	while(GetMessage(&msg, nullptr, 0, 0)) DispatchMessage(&msg);
	KillTimer(nullptr, tId);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID) {
	if(dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(nullptr, 0, Start, nullptr, 0, nullptr);
	}
	return TRUE;
}