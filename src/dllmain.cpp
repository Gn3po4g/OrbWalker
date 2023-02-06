#include "pch.h"
#include <process.h>

std::unique_ptr<Memory> m;
std::unique_ptr<Functions> f;
std::unique_ptr<OrbWalker> o;

unsigned __stdcall Start(void*) {
	m = std::make_unique<Memory>();
	f = std::make_unique<Functions>();
	o = std::make_unique<OrbWalker>();
	while(*(int*)(*(PDWORD)offsets.oGameState + 0x8) == 2) {
		Sleep(20);
		if(*(bool*)(*(PDWORD)(offsets.oChatClient) + 0x6BC)) continue;
		if((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) o->AttackObject(true);
		else if((GetAsyncKeyState('V') & 0x8000) != 0) o->AttackObject(false);
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	if(dwReason == DLL_PROCESS_ATTACH) {
		_beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
		CloseHandle(hModule);
	}
	return TRUE;
}